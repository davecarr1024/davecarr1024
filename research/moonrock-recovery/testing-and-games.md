# Building and testing games with the original MoonRock toolchain

## Conclusion

The original MoonRock compiler is usable as the foundation for a complete game-development loop. A compiler rewrite is not required for the first phase.

```text
.MOO source
   ↓
MRC.EXE
   ↓
.ASM
   ↓
ASM.EXE + MRLINK.COM
   ↓
.COM
   ↓
DOSBox
   ↓
text output, raw framebuffer, or PNG screenshot
   ↓
Codex inspection and test result
```

This lets the project answer the most important question empirically: how far can MoonRock itself go when used to build graphics programs and games?

## What has already been verified

The recovered 0.50 archive includes:

- `MRC.EXE`, the compiler;
- `MRLINK.COM`, the linker;
- ArrowSoft `ASM.EXE`;
- `MR-REF.DOC` and `MRHELP.COM`;
- many `.MOO` examples;
- `MOONROCK.ALB` and `MOONROCK.PTR`;
- `MRSRC017.ZIP`, containing compiler source and assembly libraries.

On this Linux machine, under DOSBox, the following was reproduced:

```text
MRC HELLO.MOO
ASM HELLO.ASM
MRLINK HELLO.OBJ
HELLO.COM
```

The resulting `HELLO.COM` is 276 bytes and prints `Hello world`. The generated assembly identifies itself as produced by MoonRock 0.50 and targets 8086 code.

The archive also contains concrete graphics examples:

- `STARS.MOO` uses `SETGRAPHMODE(6)`, `GETGRAPHSEG`, `SETGRAPHSEG`, `PUTPIXEL`, and `FARMEMCOPYS`;
- `WDEMO.MOO` uses an intermediate 4,000-byte screen buffer for flicker-free text rendering;
- `MR-REF.DOC` documents graphics-segment access, pixel functions, screen buffers, direct screen output, and memory operations;
- the source release contains `VIDCGA.ASM`, `DRAWLINE.ASM`, `SCRSAVE.ASM`, `FARMEM.ASM`, `MEMCPYF.ASM`, and related low-level routines.

The 0.50 sample graphics path is visibly useful, but the recovered public source release appears to predate the final binary and its `VIDCGA.ASM` focuses on CGA modes. VGA mode 13h should therefore be treated as a deliberate revival extension until the 0.50 generated library proves otherwise.

## The test layers

### 1. Pure MoonRock unit tests

The easiest tests are programs whose behavior does not depend on the screen or hardware:

- integer arithmetic;
- left-to-right expression behavior;
- arrays and bounds assumptions;
- string operations;
- coordinate transforms;
- fixed-point projection math;
- collision checks;
- tile walkability;
- portal transitions;
- sprite ordering decisions;
- game-state transitions.

MoonRock can implement a tiny assertion library using ordinary subs:

```basic
common test_count%, failure_count%

sub AssertEqual(expected%, actual%, name$)
  test_count% = test_count% + 1
  if expected% <> actual% then
    print "FAIL: " + name$ + "\n"
    failure_count% = failure_count% + 1
  else
    print "PASS: " + name$ + "\n"
  endif
end sub

sub FinishTests
  print "Tests: " + test_count% + ", failures: " + failure_count% + "\n"
  if failure_count% > 0 then
    ' Exit with a nonzero DOS errorlevel through an inline assembly helper.
  endif
end sub
```

The exact failure-exit helper should be implemented once in a small runtime module. If MoonRock’s documented `END` behavior does not expose a useful DOS errorlevel, a short inline assembly routine can call DOS interrupt 21h function 4Ch.

Each test suite should be a small `.MOO` program that prints a stable report and exits deterministically. Test programs should not depend on the current time or random state unless the test explicitly controls the seed.

### 2. Host-side compiler tests

Linux scripts can test the compiler pipeline without opening a graphics window:

1. Copy a fixture `.MOO` file into an isolated work directory.
2. Run `MRC.EXE` in DOSBox.
3. Assemble the generated `.ASM`.
4. Link the `.OBJ` into a `.COM`.
5. Check that expected artifacts exist.
6. Run the `.COM` with redirected output.
7. Compare the output and exit status.

The generated assembly should be retained for diagnostics but ignored by default in normal development. Selected assembly listings can be committed as historical evidence or golden code-generation fixtures.

An initial host runner could expose commands like:

```text
tools/moonrock-build.sh tests/math.moo
tools/moonrock-test.sh tests/math.moo
tools/moonrock-test.sh --graphics tests/stars.moo
```

The wrapper should record:

- compiler version or archive checksum;
- DOSBox version and configuration;
- source filename;
- generated artifact hashes;
- DOS exit code;
- captured stdout/stderr-equivalent files;
- screenshot or framebuffer artifact paths.

### 3. DOSBox integration tests

DOSBox is the correct execution boundary for real-mode behavior. Integration tests should cover:

- startup and clean exit;
- keyboard polling;
- timer behavior;
- file persistence;
- direct memory access;
- DOS interrupts;
- speaker access;
- graphics mode setup;
- screen-buffer switching.

Tests should use fixed inputs where possible. For keyboard tests, the launcher can send a known key sequence through DOSBox’s input automation or use a test mode that accepts scripted input from a file. Hardware behavior that cannot be made deterministic should be classified as a smoke test rather than a strict unit test.

### 4. Graphics golden tests

There are two useful forms of graphics capture.

#### DOSBox screenshots

DOSBox can capture the rendered display as PNG through its screenshot hotkey. This validates the complete visible result, including mode selection, palette, scaling, and composition.

The test program should render a known frame, pause at a known point, and then allow the runner to capture it. The launcher should use a dedicated capture directory and a predictable filename.

Screenshot comparisons are good for visual review, but they can be affected by emulator scaling or configuration. Store the DOSBox configuration with the test metadata.

#### Raw framebuffer dumps

For strict regression tests, a Mode 13h program can copy its 64,000-byte framebuffer to a mounted file before exiting. The host runner can compare the exact bytes and palette values without depending on window size or screenshot scaling.

This produces a more deterministic test:

```text
program draws frame
  → write 320×200 indexed pixels
  → write palette
  → exit
  → host compares bytes
```

Screenshots remain valuable as human-readable evidence. Raw framebuffer comparisons become the pass/fail oracle.

## Recommended first game library

The first reusable MoonRock library should stay small and match the recovered language’s strengths:

```text
runtime/
  dos-exit.moo
  keyboard.moo
  timer.moo
  speaker.moo
  vga13.moo
  framebuffer.moo
  sprite.moo
  tilemap.moo
  math16.moo
```

The implementation can mix MoonRock procedures with inline assembly and separately maintained `.ASM` modules. Keep direct hardware operations at the bottom of the dependency stack:

```text
DOS/x86 capabilities
        ↓
framebuffer and timing
        ↓
sprites, tiles, projection math
        ↓
game rules and content
```

Useful first capabilities:

```basic
Mode13
TextMode
PutPixel(x%, y%, colour%)
Line(x1%, y1%, x2%, y2%, colour%)
WaitRetrace
KeyAvailable
ReadKey
SetPalette(index%, red%, green%, blue%)
CopyFrame(source%, destination%, count&)
```

The first Mode 13h implementation can be a narrow x86 macro/runtime extension. It should set VGA mode 13h through BIOS interrupt 10h, use segment `A000h`, and calculate pixel offsets as:

```text
offset = y * 320 + x
```

That code should be isolated from the game code so it can later be replaced by a host framebuffer backend or a different VGA strategy.

## First projects

### Project 1: compiler and runtime smoke suite

Build small programs for:

- hello-world output;
- integer arithmetic;
- strings and arrays;
- file read/write;
- keyboard input;
- timer delay;
- direct screen output.

This establishes the behavior of the original compiler before adding graphics.

### Project 2: Mode 13h laboratory

Create a test card that renders:

- individual pixels at known coordinates;
- horizontal and vertical lines;
- rectangles;
- palette ramps;
- a color test pattern;
- keyboard-driven exit.

Capture both a PNG and a raw framebuffer. This becomes the first visual golden test.

### Project 3: rotating cube

Implement the old graphics-demo idea with integer or fixed-point math. Unit-test the projection and rotation functions independently, then use a golden frame to test rendering.

### Project 4: sprite and tile laboratory

Add background save/restore, transparent sprites, draw order, and a tiny 11×7 tile map. This intentionally connects the new runtime to the recovered QBasic Eastman architecture.

### Project 5: Eastman 1 — Gokarts

Build the prequel as a compact top-down racing game:

- tile-map track;
- rotating or directional kart sprites;
- collision with track edges;
- deterministic lap timing;
- simple computer opponents;
- a small number of screens.

This is an ideal MoonRock game because it exercises graphics, timing, input, fixed-point math, sprites, maps, and persistence without requiring a giant RPG.

## Codex closed loop

The Codex workflow should operate on small, observable changes:

```text
edit one .MOO or .ASM file
  → compile in DOSBox
  → run a bounded test
  → collect output/frame/screenshot
  → inspect artifact
  → report pass/fail
  → make the next change
```

Every test invocation should have a timeout. Programs should support a test mode that renders one deterministic frame and exits, instead of requiring an endless interactive loop.

Generated files should be divided into two categories:

- disposable build state: `.ASM`, `.OBJ`, temporary `.COM`, DOSBox logs, raw captures;
- curated evidence: selected generated assembly, screenshots, framebuffer fixtures, and test reports.

The archive repository currently preserves the original toolchain and a successful Hello World build. A future dedicated game repository can contain new `.MOO` source and runtime code while referring back to the recovered compiler archive and its checksum.

## Licensing and preservation

The recovered source release says it is free for personal use, provides no warranty, and prohibits commercial use. The original compiler archive and source should remain unmodified, with the original `READ.ME` and licensing text preserved.

New game source, test harnesses, runtime additions, and documentation should be clearly separated from Rowan Crowe’s recovered files. Do not represent the new Mode 13h layer or new games as original MoonRock distribution content.

## Recommended decision

Use the original MoonRock compiler now. Build a testable graphics runtime and one small game with it. Treat a compiler rewrite as a later “MoonRock 2” project informed by:

- the recovered manual;
- the recovered QuickBASIC source;
- generated assembly;
- observed DOSBox behavior;
- the needs discovered while building actual games.

That approach preserves the historical toolchain while making the new work practical, testable, and genuinely connected to the original programming experience.

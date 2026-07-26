# MoonRock language and compiler research

Date: 2026-07-25  
Subject: Rowan Crowe’s MoonRock 0.50 DOS language/compiler

## Executive summary

MoonRock is a historical, personal DOS programming language by Rowan Crowe. The available evidence describes it as a BASIC-like language with extensions, first developed in late 1994. Its distinctive goal was compact native DOS programs: 8086, 80186+, or 80386+ code, with both DOS real-mode and DPMI protected-mode support described in contemporary material.

The original toolchain is a classic multi-stage compiler pipeline:

```text
.moo source -> mrc.exe -> .asm -> assembler -> .obj -> linker -> .com
```

The original toolchain and a public source release have now been recovered. A preserved copy is in `research/moonrock-recovery/`. The archive includes `MRC.EXE`, `MRLINK.COM`, documentation, samples, ArrowSoft, and nested `MRSRC017.ZIP`, which contains `MRC.BAS` and the compiler’s assembly libraries. The toolchain has been run successfully in DOSBox on this Linux machine, producing `HELLO.ASM`, `HELLO.OBJ`, and `HELLO.COM` from `HELLO.MOO`.

## Identity and evidence quality

“MoonRock” is not a single modern language ecosystem. Search results also contain unrelated projects and the similarly named MoonScript, MoonBit, and Moon programming language. This document uses “MoonRock” only for the DOS compiler associated with Rowan Crowe and version 0.50.

Evidence is now strong enough for direct archaeology. The recovered archive identifies MoonRock 0.50 Beta, includes the command reference and samples, and provides a public-domain/personal-use source release. The source release states that the compiler was written in QuickBASIC/Visual Basic for DOS and includes roughly 10,000 lines across six `.BAS` files plus more than 5,000 lines of assembly library code. The source release prohibits commercial use, so its licensing text must travel with any preserved copy.

The original author/download site remains unavailable, but a surviving mirror at `exmortis.narod.ru` served `mrock50.zip` successfully. Its SHA-256 is recorded in `research/moonrock-recovery/README.md`.

## Recovery result

The recovered release contains:

- `MRC.EXE` — compiler;
- `MRLINK.COM` — linker;
- `MR-REF.DOC` and `MRHELP.COM` — reference documentation;
- `HELLO.MOO`, `STARS.MOO`, `WDEMO.MOO`, and many other samples;
- `ARROWASM.ZIP` containing `ASM.EXE` and `ASM.DOC`;
- `CONFIG.ZIP` containing TASM/MASM/A86/ArrowSoft configurations;
- `MRSRC017.ZIP`, a source release with `MRC.BAS`, compiler support modules, assembly libraries, build files, bug reports, and an early self-hosting rewrite under `MM/`.

The original pipeline was reproduced with DOSBox:

```text
MRC HELLO.MOO -> HELLO.ASM -> ASM.EXE -> HELLO.OBJ -> MRLINK.COM -> HELLO.COM
```

The resulting `HELLO.COM` is 276 bytes and prints `Hello world`. This is substantially more valuable than a speculative reimplementation: the original compiler is now available as a behavior and code-generation oracle.

## Language characteristics

The public descriptions support the following conclusions:

- BASIC-like syntax, with extensions beyond ordinary BASIC.
- Source files use the `.moo` extension.
- Variables use type suffixes in the available example: `b%` for an integer-like value and `a$`/`c$` for strings.
- Control flow includes `while ... wend`.
- Statements include `print`, `cls`, and an `$outstream` directive.
- String literals can include hexadecimal escape sequences such as `\h20` and newline/carriage-return escapes.
- The language exposes low-level DOS-era facilities: screen, file, port, and memory operations; memory-segment allocation; near/high/far pointers; and stack access.
- “Bundels” (spelling as reported in the source) provide C-like structures.
- Inline assembly is supported.
- Programs can choose among DOS API, BIOS, or direct video-memory output paths.
- There was an option intended to make MoonRock functions callable from QuickBASIC programs.

The example below is representative of the publicly reproduced syntax, not a complete language specification:

```basic
' MoonRock example
$outstream _tty_str_direct
cls
b% = 99
while b% > 0
  print b%
  b% = b% - 1
wend
```

The language manual is reported to have been distributed as a `.doc` file with the installation. Recovering that document is the highest-value next research step; without it, syntax and semantics should be treated as provisional.

## Compiler and output model

The documented default real-mode build has three technical stages:

1. `mrc.exe` transforms `.moo` source into assembly (`.asm`).
2. An assembler transforms assembly into an object file (`.obj`). The distribution reportedly included the free ArrowSoft assembler, and MASM was also said to be usable.
3. A linker transforms the object file into a DOS `.com` executable.

The report says a batch wrapper could expose the build as `moonrock <source-filename> [options]`. It also mentions `/‑c` and `/‑m` in sample source listings, but does not establish their meanings. The protected-mode/DPMI build procedure was not resolved by the report.

This suggests that `mrc.exe` is primarily a source-to-assembly compiler and that platform/runtime policy is represented in generated assembly plus external assembler/linker support. It also means the generated assembly is a valuable compatibility boundary: a partial native frontend could target the same style of assembly without immediately reproducing every DOS runtime detail.

## How it could work on this machine

The host inspected for this research is Linux x86-64. Available tools include GCC 12.2, Clang 14, Make, Git, and Wine. NASM, DOSBox/DOSBox-X, QEMU, and DOSEMU were not present in the command search path. Therefore:

### Option A: run the original toolchain in a DOS compatibility layer (recommended first)

1. Acquire `moon050.zip`, the MoonRock distribution, and its matching ArrowSoft assembler package from an authorized or preservation source.
2. Verify the archive with a checksum and retain an untouched copy. Do not redistribute an archive unless its license permits it.
3. Create a small isolated DOS working directory under the project, for example `davecarr1024/research/moonrock-runtime/`.
4. Use a DOS emulator or a DOS virtual machine. DOSBox-X/DOSBox is the most direct route for a DOS `.COM` workflow; a FreeDOS image in QEMU is appropriate if device or DPMI behavior requires a fuller DOS environment.
5. Mount the working directory as a DOS drive, install MoonRock and the assembler, and reproduce the documented `hello.moo` build.
6. Preserve each stage: source, generated assembly, object file, final `.com`, compiler output, emulator configuration, and a transcript of commands.
7. Run deterministic smoke tests for text output, loops, strings, files, graphics/screen operations, and any protected-mode sample separately.

Wine is installed on the host and may run `mrc.exe` directly, but it is a fallback rather than the first choice: the compiler may work under Wine while generated DOS programs still depend on DOS interrupts, video memory, or DPMI behavior. Wine also does not provide the same reproducibility as a pinned DOS image.

## BASIC alternatives

### QBasic versus QuickBASIC

QBasic is the interpreter-oriented, reduced distribution derived from QuickBASIC 4.5. It is useful for learning and interactive iteration, but it does not itself produce standalone executable files. QuickBASIC 4.5 is the relevant Microsoft DOS compiler when the goal is to build `.EXE` programs. Both are legacy Microsoft software, so acquisition and redistribution should be handled through a lawful archival source.

For graphics toy projects, QuickBASIC is a strong conceptual alternative to MoonRock because its language and examples are much better documented and its graphics model is familiar: `SCREEN`, `PSET`, `LINE`, `CIRCLE`, `GET`, `PUT`, and palette/video-page operations. The tradeoff is that it is less low-level and less distinctive than MoonRock, and its DOS executable/memory limitations are real.

### QB64 Phoenix Edition

QB64 Phoenix Edition is the best practical modern equivalent for the BASIC side of this experiment. Its stated goal is compatibility with QBasic and QuickBASIC 4.5 while compiling native binaries for Linux, macOS, and Windows. It also adds modern graphics, audio, image, window, and debugging facilities. Its documented legacy screen modes include the classic 320×200 and 640×480 modes, while its extended `_NEWIMAGE` API permits modern resolutions and color depths.

QB64-PE is not a replacement for MoonRock compatibility: MoonRock’s suffix types, directives, bundels, low-level memory model, and inline assembly would need translation. It is, however, a much better platform for a closed edit/build/run loop because it can compile and run natively on this Linux host without a DOS emulator. It also offers a useful way to prototype the graphics concept before porting the rendering logic to MoonRock.

### Bywater BASIC / other interpreters

FreeDOS distributes Bywater BASIC (bwBASIC), a GPL interpreter implementing a broad subset of classic BASIC dialects. It is useful as a lightweight, open-source DOS BASIC reference point, but it is not a close QuickBASIC compiler substitute and is not the preferred choice for graphics work. It could be useful for testing simple language-level examples or for a legally straightforward DOS interpreter in the toolchain.

### Comparison

| Toolchain | Runs natively on Linux | Produces DOS binary | Graphics fit | Historical fidelity | Best use |
|---|---:|---:|---:|---:|---|
| MoonRock 0.50 + DOSBox-X/FreeDOS | No | Yes, `.COM` | High, but hardware-specific | Highest | Preserve and explore MoonRock itself |
| QuickBASIC 4.5 + DOSBox-X/FreeDOS | No | Yes, `.EXE` | High for classic DOS graphics | High for BASIC | Authentic BASIC graphics projects |
| QBasic 1.x + DOSBox-X/FreeDOS | No | No | High for interactive experiments | High | Learn/prototype interactively |
| QB64 Phoenix Edition | Yes | Native Linux executable | Very high | Medium | Fast Codex iteration and modern output |
| FreeDOS bwBASIC | In DOS environment | Generally no native compiler output | Low/uncertain | Medium | Open-source interpreter experiments |

## Recommended closed-loop setup

The best overall setup is a two-lane workflow:

1. **Fast lane:** QB64-PE in the Linux project directory. Codex edits `.bas`, runs the compiler, executes the native binary, and checks textual output plus captured screenshots or image artifacts.
2. **Authentic lane:** MoonRock 0.50 inside DOSBox-X, backed by a pinned FreeDOS image or a mounted project directory. Codex edits `.moo`, invokes a wrapper that runs `mrc.exe`, the assembler, and linker, and collects `.asm`, `.obj`, `.com`, logs, and screenshots.

DOSBox-X is a particularly good fit for the authentic lane because its documentation covers both host-directory mounting and disk-image mounting, supports command-line configuration, and provides built-in PNG screenshots and video capture. Its screenshot shortcut is `F11`/`F12` plus `P`, depending on the configured mapper. This makes it possible to inspect graphics results without treating the emulator window as an opaque manual step.

A project wrapper should make the loop explicit:

```text
Codex edits source
  -> make moonrock-build or make qb64-build
  -> run program with a fixed input script / timeout
  -> save stdout, stderr, exit status, and generated artifacts
  -> save a PNG screenshot or a deterministic image file
  -> Codex inspects the results and edits source again
```

For MoonRock graphics, prefer programs with a deterministic startup and an explicit “quit” key. If screenshot automation is unreliable, add a test mode that writes a small framebuffer or palette dump to a mounted file; compare that file in CI and use emulator screenshots for human review. For QB64-PE, prefer writing rendered frames to PNG in test mode where possible, because file comparison is more reproducible than window screenshots.

Suggested directory additions:

```text
tools/moonrock-build.sh       # host wrapper around DOSBox-X or Wine
tools/moonrock.conf           # pinned emulator configuration
tools/qb64-build.sh           # native QB64-PE compiler wrapper
fixtures/moonrock/            # .moo programs and expected outputs
fixtures/qbasic/              # .bas programs and expected outputs
artifacts/{asm,obj,com,png}/  # generated, ignored by Git
```

The first graphics milestone should be a tiny palette-and-lines demo, not a game: set a video mode, draw a fixed set of lines/rectangles/circles, wait for a key, and exit. Once that works in both lanes, add animation, keyboard input, sprites, and sound one subsystem at a time. This keeps failures attributable to the language/runtime/emulator boundary.

### Option B: use an existing DOS toolchain from Linux

If the original compiler emits compatible 16-bit assembly, a Linux-hosted assembler/linker might be used for experimentation, but this is not guaranteed. The historical pipeline was tested around ArrowSoft/MASM-style tools and DOS object/link formats. A modern NASM/LD pipeline would likely require syntax conversion, object-format changes, or a compatibility linker. This should be attempted only after capturing the exact assembly emitted by `mrc.exe`.

### Option C: clean-room native reimplementation

A native Linux compiler can be built in the existing workspace, preferably in a new repository or a clearly isolated research subdirectory. A sensible staged design is:

```text
source text
  -> lexer with original line/column preservation
  -> tolerant parser / AST
  -> symbol and type analysis
  -> DOS-oriented IR
  -> 8086 assembly backend or a modern host backend
  -> assembler/linker adapter
```

Recommended implementation order:

1. Recover the `.doc` manual and all example `.moo` files.
2. Build a corpus inventory and identify syntax, types, calling conventions, directives, and runtime calls.
3. Implement a lexer and parser for comments, identifiers, suffix-typed variables, literals/escapes, assignment, `print`, `cls`, `while/wend`, and expressions.
4. Implement an interpreter or a high-level reference evaluator first. This gives fast semantic tests before dealing with 16-bit code generation.
5. Add a compiler backend that emits readable pseudo-assembly, then real 8086 assembly for a narrow subset.
6. Reproduce the DOS runtime incrementally: console output, strings, arithmetic, file I/O, then graphics, ports, far pointers, and inline assembly.
7. Add golden tests comparing output and, where appropriate, generated assembly against the original compiler.

For a modern implementation, Rust or C++ would both fit the host environment. Rust would make the lexer/parser/compiler data model safer; C++ would align more naturally with existing low-level tooling. For the first proof of concept, a small Python reference interpreter is likely fastest, but it should not be mistaken for a production compiler or a license-clean replacement until the historical material is understood.

## Codex workflow on this machine

Codex can help with the project as a repository-based, test-driven preservation effort:

- Keep a `README.md` describing provenance, legal status, acquisition notes, and reproducible commands.
- Keep original binaries and downloaded archives out of Git unless redistribution is explicitly allowed; store checksums and local paths instead.
- Ask Codex to inspect one recovered manual section or one sample at a time, extracting grammar and behavior into a living `docs/language-notes.md`.
- Have Codex implement one small compiler slice per change, with a fixture, expected diagnostic behavior, and a generated-artifact snapshot.
- Use a `Makefile` or shell scripts to make emulator invocation, corpus testing, and artifact collection repeatable.
- Run native unit tests on every change and run DOS/emulator tests when the emulator and original assets are available.
- Treat inline assembly, raw ports, direct video memory, and file operations as explicit capability boundaries. They should be tested in an isolated DOS image rather than executed on the Linux host.

A useful initial layout is:

```text
davecarr1024/research/moonrock/
  README.md
  docs/language-notes.md
  docs/provenance.md
  corpus/                  # recovered samples; licensing recorded
  fixtures/                # small test programs
  src/                     # native reimplementation, if pursued
  tools/                   # emulator/build wrappers
  artifacts/               # ignored generated .asm/.obj/.com files
```

The first Codex task should be an acquisition-and-reproduction task, not a rewrite: establish whether the original compiler can compile `hello.moo`, capture its assembly, and determine whether the manual and examples are sufficient to define a minimal grammar.

## Risks and open questions

- The recovered source release is version 0.17-era/public-source material bundled with the 0.50 distribution; whether it exactly rebuilds the 0.50 `MRC.EXE` remains to be tested.
- The author’s current distribution location is unavailable, but the mirror archive and checksum are recorded.
- The full grammar, type system, runtime ABI, command-line options, and protected-mode support need the original manual or binaries for confirmation.
- ArrowSoft assembler/linker compatibility may be difficult to reproduce on a current Linux host.
- DOS graphics, ports, and memory-segment features cannot be meaningfully validated solely through a Linux-native test runner.
- A clean-room reimplementation should avoid copying implementation code or undocumented proprietary assets; derive behavior from lawfully obtained documentation, observable tests, and independently written code.

## Research conclusion

MoonRock is a recovered historical DOS compiler, not a currently maintained general-purpose language. The lowest-risk path is now to preserve and exercise the original `.moo -> .asm -> .obj -> .com` pipeline, inventory its real graphics and hardware capabilities, and use the captured outputs/manual/source to guide a narrow native implementation. The “wedding cake” project can be grounded in the real compiler rather than merely imitating descriptions of it.

## Sources

- [MoonRock on DOS — installation and technical overview](https://www.streetinfo.lu/computing/programming/dos/dos_moonrock.html) — primary accessible technical description used for the pipeline, language features, platform targets, and limitations.
- [Philipp Winterberg, “MoonRock 0.50” excerpt](https://d-nb.info/1358655383/34) — archival reproduction identifying the 1998 freeware DOS compiler and showing a `.moo` sample/build sequence.
- [Rowan Crowe’s MoonRock page](https://www.rowan.sensation.net.au/moonrock.html) — author/download page referenced by the archival sources; availability was not independently verified during this research.
- [Recovered MoonRock mirror archive](https://exmortis.narod.ru/comp_src/mrock50.zip) — served the 551,055-byte `mrock50.zip` archive used for the local recovery; checksum and extracted contents are recorded in `research/moonrock-recovery/`.
- [Compiler source index](https://exmortis.narod.ru/src_compilers_eng.html) — historical index identifying `mrock50.zip` and its claimed source/output model.
- [FreeDOS compiler list](https://www.geocities.ws/snoopimeanie/freedos.htm) — historical index describing MoonRock as a semi-open-source BASIC-to-assembly compiler using ArrowSoft.
- [DOSBox-X home and feature overview](https://dosbox-x.com/) — current emulator project and target use cases.
- [DOSBox-X introduction](https://dosbox-x.com/wiki/Home) — mounting, screenshots, and keyboard shortcuts.
- [FreeDOS download page](https://www.freedos.org/download/) — current FreeDOS release and emulator guidance.
- [QB64 Phoenix Edition](https://www.qb64phoenix.com/) — native cross-platform BASIC-compatible compiler/project.
- [QB64-PE SCREEN documentation](https://qb64phoenix.com/qb64wiki/index.php/SCREEN) — legacy and extended graphics modes.
- [FreeDOS bwBASIC package](https://www.ibiblio.org/pub/micro/pc-stuff/freedos/files/repositories/1.3/html/en/devel/bwbasic/20241115.0/index.html) — open-source DOS BASIC interpreter package.
- [QuickBASIC overview](https://en.wikipedia.org/wiki/QuickBASIC) — QBasic/QuickBASIC relationship and compiler distinction; used as secondary historical context.

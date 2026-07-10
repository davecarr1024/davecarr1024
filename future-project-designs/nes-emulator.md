# NES Emulator Design Doc

## Core Question

Can a real 8-bit console be modeled as a small deterministic world where hardware behavior becomes visible, testable, and playable?

The seed is not "build another CPU simulator." The seed is a complete console as an executable artifact: cartridge, CPU, PPU, memory map, controller input, frame timing, and a tiny set of known games or test ROMs that prove the machine is alive.

The satisfying part would be seeing a real program run because the model is coherent end to end.

## Fantasy

I am building a transparent NES.

I can run a small ROM, see the frame, inspect CPU state, inspect PPU state, step through frames or instructions, and understand why the screen changed.

The product is behavioral accuracy in service of understanding. Unlike IRATA2, where I deliberately sacrificed real 6502 behavior to keep the system elegant, microcoded, and clean at every point in time, this project would move slightly beyond that model. The goal would be to model what the NES hardware does accurately enough to run real software, even when that means not modeling exactly how the 1970s silicon achieves it.

That shift is the interesting part: the emulator would still be deterministic, inspectable, incremental, and verified, but its "truth" would be observable hardware behavior rather than an idealized hardware-ish design.

## Fundamental Object

`Frame`.

The frame is the proof that the whole console cooperated correctly for one visible interval of time.

Everything interesting feeds into the frame:

- CPU instructions modify memory and PPU registers.
- PPU state produces pixels.
- Cartridge mapping determines what code and graphics are visible.
- Controller input changes program behavior.
- Timing determines when state changes become visible.
- Tests can compare frames, traces, or state checkpoints.

The CPU matters, and the first serious step is probably a cycle-accurate 6502-family CPU. But the CPU should be modeled as the NES needs it: an accurate behavioral component inside a whole console, not another elegant fake computer architecture.

IRATA, PIRATA, BCS, Flip, Bitta, and IRATA2 already explore CPUs and digital logic from the "how could this be built?" direction. A NES emulator should move toward "what does this real machine do, cycle by cycle, and can I explain the effects?"

## Key Shift From IRATA2

IRATA2 is clean because everything is defined by the model:

- pure microcode,
- explicit tick phases,
- hardware-ish components,
- no magic,
- verifiable state at every layer,
- behavior that exists because the modeled machine says it exists.

A NES emulator would not have that luxury. Real 6502 behavior includes timing, bus accesses, addressing quirks, interrupt behavior, DMA interactions, PPU timing, and other details that are not naturally derived from a clean hobby HDL model unless I commit to transistor-level or extremely low-level reproduction.

I am not a 1970s microprocessor designer, and the goal is not to rediscover every silicon optimization that made an instruction one cycle shorter. The practical emulator model needs a different kind of honesty:

- hardcode the known behavior of instructions,
- represent each cycle's externally visible effects,
- model bus reads and writes at the right times,
- preserve observable quirks,
- verify against test ROMs and known traces,
- explain the behavior without pretending it emerged from a perfect internal hardware model.

This is "what-modeling" rather than "how-modeling."

The magic is acceptable if it is explicit, localized, documented, and test-backed. A table saying "this instruction performs these bus operations over these cycles" is not a failure. It is the right abstraction for a behaviorally accurate emulator.

## Non-Goals

- Do not start with a perfect emulator.
- Do not start with every mapper.
- Do not start with audio.
- Do not start with save states.
- Do not start with debugger UI polish.
- Do not start with cycle-perfect PPU edge cases.
- Do not support arbitrary commercial ROMs in v1.
- Do not turn this into a generic emulation framework.

V1 should not chase completeness. It should run a tiny known target and explain itself.

## V1 Thesis

The smallest worthwhile v1 is:

- load one simple iNES ROM,
- implement a small cycle-accurate 6502 subset for that ROM,
- implement the CPU memory map needed by that ROM,
- implement enough PPU behavior to draw a deterministic frame,
- accept simple controller input or scripted input,
- produce inspectable CPU/PPU/frame traces,
- pass focused CPU, PPU, memory-map, and frame tests.

If the first real frame appears and can be explained, the project has earned its next layer.

## Model Objects

- `Cartridge`: ROM data, header, mapper, PRG, CHR, mirroring.
- `Cpu`: 6502-family CPU state, instruction execution, cycle schedule, and externally visible bus operations.
- `InstructionPlan`: behavior-level description of what an opcode does on each cycle.
- `Bus`: CPU-visible memory map and device routing.
- `Ppu`: picture processing unit state, pattern tables, name tables, palettes, sprites, scanline/frame progression.
- `Controller`: input state sampled by the emulated program.
- `Clock`: deterministic timing coordinator.
- `Frame`: pixel buffer plus metadata about how it was produced.
- `Trace`: structured record of CPU steps, PPU events, memory reads/writes, and frame boundaries.
- `RomFixture`: test ROM or minimal handcrafted program with expected behavior.

## First Questions

- Can a ROM be loaded and validated?
- Can the CPU execute a minimal program with the right cycle-by-cycle bus effects?
- Can an instruction explain what it does per cycle without pretending to model transistor-level cause?
- Can writes to PPU registers produce visible pixel output?
- Can the emulator produce the same frame from the same ROM and input every time?
- Can a failed frame explain whether the CPU, bus, cartridge, or PPU caused the mismatch?
- Can tests assert meaningful checkpoints without reverse-engineering logs?

## First Runnable Moment

The first delightful runnable moment is not a full game. It is a tiny ROM producing a known image:

```text
Loaded: hello-background.nes
Mapper: NROM
CPU steps: 18422
Frames: 1

Frame 0:
  background palette: loaded
  nametable writes: 960
  sprite count: 0
  checksum: 7b3a9e41

Status:
  CPU: ok
  PPU: ok
  Frame match: yes
```

The visual result can be simple: colored tiles, a test pattern, or a known homebrew test ROM. The important part is that it is a real frame from an emulated console pipeline.

## Representation Principle

Keep the console boundaries explicit.

The emulator should not become a pile of callbacks. It should have clear ownership:

- CPU talks to a bus.
- Bus routes to RAM, PPU registers, controller, and cartridge.
- Cartridge owns mapper behavior.
- PPU owns video memory interpretation and frame output.
- Trace observes without controlling behavior.

The trace/debug layer must not change the machine. It should be like Bitta's contracts: observation and judgment are separate from physics.

For the CPU, prefer a behavior table or instruction-plan representation over a fake microcode story. Each opcode should have an explicit sequence of externally visible effects:

- fetch opcode,
- read operand bytes,
- perform dummy reads if needed,
- read or write effective addresses,
- update registers and flags at the correct point,
- consume the correct number of cycles,
- expose enough trace data to explain the instruction.

This is where the project intentionally diverges from IRATA2. IRATA2 asks for elegant internal causality. NES emulation asks for faithful observable behavior. The design can still be elegant, but it should be honest about where the behavior is hardcoded.

## Testing Principle

The proof suite is the product.

Useful tests:

- CPU instruction tests for the supported subset,
- per-cycle CPU bus-operation tests,
- addressing-mode tests,
- bus mirroring tests,
- cartridge header and mapper validation tests,
- PPU register behavior tests,
- palette/name-table/pattern-table rendering tests,
- frame checksum or golden-image tests for tiny ROMs,
- deterministic replay tests for scripted input,
- trace tests that assert structured events.

Avoid relying only on manual visual inspection. The frame is visible, but it should also be assertable.

## V1 Scope

V1 includes:

- iNES loading for NROM only,
- enough cycle-accurate CPU instructions for selected test ROMs,
- per-instruction cycle plans for that subset,
- CPU RAM and basic memory mirroring,
- PPU register interface needed for simple background rendering,
- pattern table, nametable, and palette rendering for background tiles,
- one pixel/frame output path,
- scripted controller input if needed,
- structured traces,
- golden-frame or checksum tests.

V1 excludes:

- APU/audio,
- most mappers,
- save states,
- rewind,
- netplay,
- full debugger UI,
- cycle-perfect sprite behavior,
- arbitrary commercial compatibility,
- dynamic recompilation,
- emulator frontend polish.

## Growth Path

### Layer 1: ROM To Frame

Load a tiny NROM program and render a deterministic frame.

### Layer 1a: Cycle-Accurate CPU Slice

Before the first meaningful frame, build the smallest cycle-accurate 6502 slice needed by the ROM target. The deliverable is not a full CPU; it is a verified instruction-plan mechanism with a handful of opcodes, addressing modes, flags, and bus operations.

### Layer 2: CPU And PPU Confidence

Expand instruction and PPU behavior using focused test ROMs and traceable failures.

### Layer 3: Playable Minimal Game

Run one simple homebrew or public-domain game with controller input and stable frame pacing.

### Layer 4: Debugger As Product

Add inspectable state: CPU registers, disassembly, memory view, PPU tables, frame history, and event trace.

### Layer 5: Compatibility Expansion

Add mappers, sprites, scrolling edge cases, audio, and broader ROM support only after the console model is coherent.

## Fit Analysis

### Fit Score

NES Emulator is a strong thematic fit but a risky execution fit.

| Goal | Fit | Notes |
| --- | --- | --- |
| Small deterministic world | Medium | The NES is deterministic, but not small unless v1 is aggressively constrained. |
| One fundamental object | Medium | `Frame` can organize the project, while `InstructionPlan` organizes the CPU accuracy slice. |
| Causality and explanation | Strong | Traces can explain why pixels appeared and which cycle-level instruction/register writes caused them. |
| Tests as proof | Strong | CPU cycle tests, bus tests, PPU tests, and golden-frame tests align well. |
| Start delightfully small | Medium | First frame is delightful, but getting there requires several cooperating subsystems. |
| Avoid generic-engine trap | Medium | The danger is building a reusable emulator framework or another CPU platform. |
| Personal hook | Strong | It directly answers what happens when the clean IRATA2 approach yields to real machine behavior. |
| Execution risk | High | Emulation accuracy, PPU timing, mapper behavior, and compatibility can expand without limit. |

### Why It Might Be Worth Building

This could be the most concrete payoff for the virtual-computer thread. IRATA and PIRATA ask what it is like to make a fake console. IRATA2 asks how clean and verifiable a hardware-ish model can be when I own the whole machine definition. A NES emulator asks whether a real console can be made understandable when the design has to respect behavior I did not invent.

The best version would be less "yet another emulator" and more "an executable annotated NES textbook."

The core learning value is the mindset shift:

- IRATA2: model the how cleanly, then derive behavior.
- NES emulator: model the what faithfully, then explain behavior.

That is a real next step rather than a repeat, if the project stays honest about this distinction.

### Main Risks

- It directly triggers the "another CPU simulator" warning.
- Accuracy work can become endless.
- The "magic" in instruction behavior could become scattered and untestable if not localized.
- PPU behavior is subtle and can dominate the project.
- Compatibility pressure can replace understanding as the goal.
- A polished frontend/debugger can become a UI project before the model is proven.

### Scope Guardrails

- V1 must target one mapper: NROM.
- V1 must target one or two tiny ROM fixtures, not "NES compatibility."
- V1 must define frame output as the central proof.
- V1 must make CPU cycle behavior explicit and test-backed.
- V1 must keep hardcoded instruction behavior localized in instruction plans or equivalent tables.
- V1 must separate emulation state from tracing/debugging.
- V1 must stop before audio unless the video pipeline is already proven.

### Recommended Execution Plan

1. Write the project `README.md` and `docs/design.md` with the v1 ROM target named explicitly.
2. Build cartridge loading and NROM validation.
3. Build an `InstructionPlan` or equivalent mechanism for explicit per-cycle CPU behavior.
4. Build CPU core only as far as the first ROM requires, with instruction and per-cycle bus tests.
5. Build bus routing and memory mirroring tests.
6. Build minimal PPU register behavior and background tile rendering.
7. Produce one deterministic frame and assert it with a checksum or golden image.
8. Add trace output that connects CPU cycles and writes to PPU state and frame results.
9. Write a v1 postmortem before adding mappers, sprites, audio, or compatibility goals.

## Relationship To Existing Projects

- `IRATA`: fake console vision and whole-stack joy.
- `PIRATA`: Python CPU simulator lessons, especially traceability and avoiding parallel HDL.
- `IRATA2`: stable layers, strong types, generated definitions, tests as proof, and a useful contrast: clean internal model over real 6502 accuracy.
- `Bitta` / `Flip` / `BCS`: hardware and CPU modeling pressure, but also warning signs about repeating the same project.

The NES emulator should only proceed if its thesis is "make a real console explain itself through faithful observable behavior," not "write another elegant fake CPU."

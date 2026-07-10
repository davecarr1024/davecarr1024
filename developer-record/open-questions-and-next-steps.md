# Open Questions And Next Steps

Last synthesized: 2026-07-10.

This document summarizes the current developer record, project inventory, and future-project design shelf. It is meant to keep the next decisions visible without turning early ideas into commitments.

## Current Read

The developer record is now coherent around one central thesis:

> Build small deterministic worlds where hidden systems become visible, causal, inspectable, and testable.

The strongest operating goal is not being stuck. The preferred work mode is a loop of choosing the next bite-size piece, designing it, implementing it, verifying it, and leaving behind a stable building block.

The main historical warning is also clear: avoid naked engines and abstraction stacks that lose contact with a concrete runnable world. The repeated project families in the inventory make this especially important for language/compiler work, board-game AI, and simulation engines.

The agent-enabled development process is now explicit: brainstorm and discuss the idea, name it, write the initial design, plan phases and checkpoints, execute in verified bites, and close each phase with a checkpoint note.

## Cross-Project Open Questions

### Which future project should become the next real repo?

Paper Railroad remains the best first candidate by execution fit. It has a small non-UI v1, a strong core object, natural tests, and a direct personal hook.

Compiler Lab may be the strongest educational candidate. It is useful if the explicit goal is to learn standard compiler concepts through visible artifacts, not to invent another language framework.

NES Emulator is the highest-risk virtual-computer candidate. It is worthwhile only if the thesis stays focused on transparent behavioral accuracy: model what the real machine does, not an idealized clean CPU architecture.

Game AI Lab is promising, but it has the clearest abstraction trap. It should start only if the first milestone is one generic policy playing two concrete games, not a board-game framework.

### How should designs move from this repo into project repos?

The rule is:

- `davecarr1024` keeps my overall developer structure, recurring patterns, standards, agent process, inventory, and future designs.
- Early project ideas stay in `future-project-designs/` while they are still being brainstormed, named, and shaped.
- After initial design discussion, naming, and repo creation, the active project design moves into that project's repo.
- The new project repo should be created with a root `README.md`, `docs/design.md`, and project-local `AGENTS.md` or `agents.md`.
- The future-design file in `davecarr1024` should either become an origin note or a short pointer to the project repo.
- Cross-project lessons, postmortems, reusable standards, and durable philosophy come back into `developer-record/`.

The active design should live next to the implementation once implementation starts. The root developer record should preserve the pattern, not become the working design source for every active project.

### How should project names be handled?

Every project needs a good punchy name during initial brainstorming. The name should clarify the project before implementation starts.

Open naming questions:

- Is `Paper Railroad` the final name, or a design label that wants a sharper project name?
- Is `Compiler Lab` too generic for the project once its point of view is clearer?
- Is `Game AI Lab` a placeholder, with the real name emerging from the first concrete game pair?
- Does the NES emulator need a name that signals "transparent behavioral console" rather than generic emulation?

Good names should be short, memorable, and tied to the core object, fantasy, historical reference, or personal hook.

## Project-Specific Next Steps

### Paper Railroad

Decision: Keep as lead candidate.

Next useful bite:

1. Decide whether `Paper Railroad` is the implementation name or only the concept name.
2. Create a project repo with `README.md`, `docs/design.md`, and `AGENTS.md`.
3. Define the smallest map format: towns, routes, goods, producers, consumers.
4. Implement validation only.
5. Add tests for invalid towns, disconnected routes, unknown goods, and unbalanced demand.
6. Add waybill derivation and route-load explanation after validation is stable.

Open questions:

- What is the first map?
- Should v1 be Python for speed and test ergonomics, or C++ for strong modeling?
- What does one excellent explanation look like?
- What design regret should v1 intentionally be allowed to expose?

### Tower

Decision: Best second railroad candidate if proof and causality are the desired energy.

Next useful bite:

1. Sketch one fixed junction as data.
2. Define the route table and denial reasons before UI.
3. Prove route clear/deny cases in tests.
4. Add the smallest panel only after the route model can explain itself.

Open questions:

- What real or fictional interlocking should inspire the v1 plant?
- Should the UI be text-first, terminal panel, or small browser canvas?
- How much signal realism is enough to teach the idea without scope creep?

### Janney

Decision: Best tactile/playable railroad candidate, but higher tuning risk.

Next useful bite:

1. Keep the first model one-dimensional.
2. Define coupler state and coupling thresholds.
3. Prove deterministic replay and basic coupling invariants.
4. Add one fixed inglenook only after the core car/coupler model works.

Open questions:

- What is the simplest physics model that makes switching legible?
- How will "feel" be evaluated without letting tuning swallow the project?
- Can the first version avoid a layout editor entirely?

### NES Emulator

Decision: Strong idea, but only as a behaviorally accurate "what-modeling" project.

Next useful bite:

1. Pick one tiny NROM target ROM or handcrafted ROM fixture.
2. Define the `InstructionPlan` representation for a minimal 6502 subset.
3. Write per-cycle bus-operation tests for that subset.
4. Load ROM data and execute a tiny program before touching broad PPU behavior.

Open questions:

- What is the first ROM target?
- What external CPU/PPU reference traces or test ROMs should be treated as authority?
- How much CPU subset is needed before the first frame?
- What should the project name communicate: NES, transparency, traceability, or behavioral accuracy?

### Compiler Lab

Decision: Strong educational candidate if it stays artifact-first.

Next useful bite:

1. Pick a punchy project name before implementation.
2. Choose the v1 implementation language and test style.
3. Define the tiny source language and grammar.
4. Build lexer plus token-span diagnostics.
5. Add parser, AST, semantic analysis, TAC, VM lowering, and execution one verified stage at a time.

Open questions:

- Should the v1 parser be recursive descent or Pratt?
- Should the target VM be register-based or stack-based?
- What standard compiler textbook or course should guide vocabulary?
- What is the first historical stretch: C-like frontend, standard-ish IR, or ELF output?

### Game AI Lab

Decision: Worth preserving, but it must earn abstraction through concrete games.

Next useful bite:

1. Pick two v1 games.
2. Implement one game completely before defining the generic interface too broadly.
3. Add minimax or alpha-beta with move explanations.
4. Add the second game and let it force interface changes.

Open questions:

- Which two games best expose a shared interface without being too similar?
- Should the first game be Tic-Tac-Toe because it is exhaustively solvable, or something slightly richer?
- What does "one AI plays many games effectively" mean in measurable v1 terms?
- What name captures the idea better than `Game AI Lab`?

## Standards To Add To New Project Creation

Before creating a new project repo, answer:

- What is the punchy name?
- What is the core question?
- What is the fundamental object?
- What is the first runnable moment?
- What is explicitly out of scope for v1?
- What test or inspectable artifact proves the first milestone?
- What old failure mode is this project most likely to repeat?
- What are the v1 phases, deliverables, and checkpoints?
- What verification step proves each phase?

Then create:

- `README.md`
- `docs/design.md`
- optional `docs/roadmap.md`
- `AGENTS.md` or `agents.md` when project-local guidance differs from the root defaults

During execution, follow `agent-enabled-development-process.md`.

## Recommended Immediate Next Step

Do not start three repos.

Choose one of two paths:

1. Start Paper Railroad V1 if the goal is maximum fit with the current developer-record compass.
2. Do a naming and scoping pass across all future ideas if the goal is to keep the design shelf sharper before implementation.

Either path should preserve the not-being-stuck loop: name the thing, shrink the first milestone, define done, verify it, and record the lesson.

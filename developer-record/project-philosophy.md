# Project Philosophy

This is the durable content from the old `~/projects/projects.html` page, converted into the root developer record.

## Core Thesis

I should build small, deterministic worlds whose behavior emerges from simple rules, where every interesting event has an understandable cause and every important state can be inspected, replayed, tested, or explained.

The durable pattern is not CPUs, trains, puzzles, databases, or games by themselves. It is building miniature executable models where hidden causal systems become tangible.

## High-Level Goal: Not Being Stuck

A major goal of my development practice is not being stuck.

Not being stuck means moving steadily forward on a project without getting bogged down by details, ambiguity, or architectural fog. It does not mean rushing. It means being able to repeatedly identify the next bite-size piece of work, design a solution to it, implement that design, verify the implementation, and deliver a complete sub-module of the overall system to a defined standard.

The ideal unit of progress is small but real:

- clear enough to design,
- bounded enough to implement,
- testable enough to verify,
- complete enough to become a building block,
- documented enough that the next step is easier.

I love this work mode. It is the mode where a project keeps producing stable footholds instead of accumulating vague intent.

Agent-driven development is a major tool for maintaining this state. It helps me:

- do deeper design discussion and review up front,
- identify the next coherent piece of work,
- choose coding and testing practices deliberately,
- supervise development while understanding each action being taken,
- keep implementation moving without losing design control,
- finish sub-modules to a standard that lets them support later layers.

This has worked well in both work and hobby development, and I enjoy it. Maintaining this flow should be treated as a first-class project goal, not merely a productivity tactic.

See `agent-enabled-development-process.md` for the explicit project process: brainstorming and discussion, naming, initial design, phases, deliverables, checkpoints, execution, verification, and phase completion.

### Operating Loop

The work loop I want to preserve is:

1. Brainstorm the seed question.
2. Name the project.
3. Write the initial design.
4. Plan phases, deliverables, and checkpoints.
5. Identify the next bite-size piece.
6. Define what done means.
7. Design the local solution.
8. Implement the design.
9. Verify with tests, checks, or an inspectable artifact.
10. Deliver the sub-module as a stable building block.
11. Use what was learned to choose the next bite.

When a project feels stuck, the fix is usually to shrink the next step, sharpen the proof of done, or return to the concrete model.

## The Seed Is A Question

My best projects do not start with "I want to build a compiler" or "I want to build a database." They start with curiosity:

- What does a minimum computer look like?
- What does consensus look like?
- Why does dispatching feel interesting?
- What makes schedulability hard?
- What makes a proof satisfying?

The product is understanding. I am not trying to build production software. I am trying to build executable models that make hidden systems tangible enough to understand from the inside.

## The Cliff Edge

My recurring failure mode is letting architecture become more interesting than the thing being built: a universal framework, naked engine, production-shaped subsystem, or abstraction stack that loses contact with a runnable experience.

## Past Projects As Evidence

### IRATA / PIRATA / IRATA2

Virtual computers built from language, assembler, microcode, HDL, simulator, tests, demos, and debug tooling.

What I learned: layered systems are joyful when every layer earns the next one and can be tested, inspected, and used as stable footing.

Tags: earned layers, testability, single source of truth.

### Sudologue / Sudoku / Banana

Logic and word solvers built around constraints, proof chains, propagation, rollback, and explanation.

What I learned: the satisfying part is not only finding an answer; it is understanding why the answer is forced.

Tags: proof, constraints, causality.

### Tracky

A virtual model railroad platform for layout building, train handling, switching puzzles, sandbox operation, and eventual automation.

What I learned: a small operational world can stay charming while still supporting dispatching, automation, load movement, and emergent behavior.

Tags: operations, railroad, world model.

### Eastman / Henka

A data-driven text RPG and an adaptive shooter, both centered on a concrete playable loop with deterministic systems behind it.

What I learned: personal hooks and live feedback matter. I stay with a project when I have something to play, watch, or explore early.

Tags: playable core, feedback, personal hook.

### Doki

A learning distributed key-value database with replication, sharding, recovery, planned durability, and growing production-shaped concerns.

What I learned: serious-system models need a tight explanatory center. Without one, reasonable subsystems accumulate faster than understanding.

Tags: postmortem, distributed systems, scope drift.

### Pysh6 / GBGE

A deep parser/compiler frontend stack and a generic board-game engine experiment.

What I learned: elegant abstractions can still become hard to change if every layer remains load-bearing and no single concrete experience anchors the engine.

Tags: abstraction risk, rules engines.

## Lessons From Success And Failure

### IRATA2: Stabilized Layers

IRATA2 is my gold standard because it is decomposed into stable layers: base types, HDL structure, ISA source of truth, generated definitions, microcode IR and validators, simulator runtime state, assembler, tests, demos, and debug tooling.

### Doki: Too Many Serious Systems

Doki expanded from a visible distributed-system model into replication, durability, leader election, dynamic sharding, operations, reliability, and SQL. I let the surface area grow faster than my ability to explain one behavior clearly.

### Pysh6: The Stack Of Furniture

In Pysh6 I successfully stacked regex, lexer, parser, parser framework, Pysp, Pype, and Pysh. It tipped when changing anything required pulling apart the whole vertical stack and rebuilding too much working memory at once.

### Versioning Is A Release Valve

My v1 is allowed to be wrong. The healthy pattern is IRATA to IRATA2: build a concrete version, extract real design regrets, then make v2 smaller and clearer. The dangerous loop is restarting before the current version has taught me something specific.

## Pattern Rules

| Pattern | Lesson | My Rule |
| --- | --- | --- |
| IRATA2 HDL, ISA, microcode, sim, assembler, tests | Each layer owns one kind of truth and emits an artifact the next layer can trust. | I should freeze contracts as I climb. If a change requires re-deriving the whole stack, I should cut a boundary. |
| Doki roadmap and subsystem growth | Production-shaped complexity can crowd out the model's explanatory center. | I should keep real-world inspiration, but fictionalize implementation until the causal model is clear. |
| Pysh6 parser/compiler stack | Elegant abstractions are still dangerous when every layer remains live and interdependent. | I need every layer to produce an inspectable artifact: token trace, parse tree, typed AST, IR, executable result, or diagnostic. |
| GBGE and board-game engines | A generic engine is less satisfying than one complete game whose rules can be explained. | I should build one concrete experience before extracting a framework. |

## Design Principles

### Build Executable Models

I should prefer miniature worlds over utilities: a computer to inhabit, a railroad to operate, a cluster to watch, a puzzle universe to reason inside.

### Preserve Causality

Seeing what happened is not enough. I want the system to explain why it happened through proofs, traces, timelines, occupancy diagrams, and state transitions.

### Compress, Do Not Generalize

I want the smallest set of rules that generates rich behavior. Good models compress; generic frameworks often expand.

### Encode Truth Once

I want every important fact to exist in one place. Documentation, visualizations, tests, diagnostics, and tools should derive from the model instead of becoming parallel descriptions.

### Make Invalid States Unrepresentable

I should use the type system, generated definitions, validators, and structured data to encode invariants whenever they clarify the model. I would rather teach the compiler the rules of the world than repeatedly check them by hand.

### Design For Proof

Testability is representation design. My model should expose builders, fixtures, structured results, intermediate artifacts, and diagnostics so tests can describe the world directly.

Thoroughly testable code is a very good sign. When code can be covered cleanly, it usually means the model has stable boundaries, visible state, and useful public artifacts. When coverage is painful, that is often a code smell: concepts may be hidden, responsibilities may be mixed, or the design may not expose the right checkpoints.

### Tests Are The Deliverable

For my projects, the proof is the product. A demo is nice, but the deeper pride is a full run: every layer exercised, every invariant checked, every expansion covered, 100% pass, and 100% production-code coverage as the standard goal.

Every project should have a test command, a coverage command, and a presubmit or all-check command that at least enforces tests passing. Mature projects should enforce coverage too, with narrow documented exceptions when full coverage is not practical.

### Readable Tests Are Elegant

I want tests that set up the world, perform the action, and assert the meaningful final state. A thousand lines of boilerplate, mocks, and incidental special cases is not a satisfying proof.

### Avoid Administrative Complexity

Interesting complexity teaches me something. Administrative complexity is config, deployment, retries, compatibility, lifecycle, and API surface. I should aggressively avoid the latter in hobby projects.

### Depth Beats Breadth

The best growth adds one more causal layer to the central model: proof generation, signal timing, route capacity, lineage, accounting, trace replay, or scheduler pressure.

### Earn The Next Layer

Bits become registers, registers become instructions, instructions become assembly, assembly becomes programs, programs become games. I want each layer to feel inevitable, not magical.

### Start Delightfully Small

I should build one runnable thing quickly: one proof, one train movement, one replicated write, one dungeon room, one map analysis. That moment is not a milestone; it is the fuel.

### Name The Project

Every project needs a good name.

The name should be part of the initial brainstorming process, not a late branding pass. A strong name gives the project a handle, makes the idea easier to return to, and forces a little early clarity about what the project is really about.

Historically, I have often used codenames or compressed names:

- `pysh`: C# or shell-like language ideas in Python.
- `fge`: the Flyin' Hawaiian game engine.
- `IRATA`: a poor Atari-like emulator idea, with a name connected to `errata` and `Atari` reversed.

I like those names because they make projects feel personal and distinct. They are best for proper-noun projects that are creative, releasable, or product-like: a game, utility, tool, simulator, or world that should have its own identity.

Experiments, labs, and educational projects should usually have descriptive names. `compiler_lab` and `game_ai_lab` are not as evocative as codenames, but they are honest, searchable, and scope-setting. For educational or exploratory projects, that clarity is more useful than mystery.

The best names are short, memorable, and connected to either the core object, fantasy, historical reference, emotional hook, or plain project purpose. `Janney`, `Tower`, `Paper Railroad`, `IRATA`, `Henka`, `Sudologue`, `compiler_lab`, and `game_ai_lab` can all be valid if the name helps the project stay concrete.

The practical rule is:

- Proper-noun creative/releasable projects should get short, punchy, often punny names.
- Experiments, labs, and educational projects should get descriptive names.

The naming standard is not polish. It is focus. If an idea cannot yet support a name, that may mean the seed question is still too vague.

### Preserve Forward Motion

I should structure projects so there is always a next useful bite. The next step should be small enough to finish, meaningful enough to matter, and verified enough to become a stable building block for later work.

## Future Direction

The strongest current direction is `Railroad Worlds`: a family of small executable models rather than one giant simulator.

- Paper Railroad asks what should move.
- Janney asks how it moves.
- Tower asks when it may move.

See `../future-project-designs/railroad-worlds.md` and `../future-project-designs/paper-railroad.md`.

Another future candidate is `NES Emulator`: a transparent, testable emulator centered on producing and explaining frames from a real console model. It fits the virtual-computer thread, but it should only proceed if the thesis is "make a real console explain itself," not "write another CPU."

Another future candidate is `Compiler Lab`: a small learning compiler focused on fundamentals, three-address code, a tiny execution environment, and visible artifacts at every stage. It fits if it repairs the Pysh failure mode by compiling one concrete language before building parser frameworks or chasing a dream language.

Another future candidate is `Game AI Lab`: a return to the GBGE / ESS idea of a generic board-game representation and AI system. It fits if the abstraction is earned by concrete games: one AI policy should play at least two small deterministic games through the same interface before the project claims generality.

## Projects I Should Probably Avoid

- Another CPU simulator unless it serves a new visible experience.
- Pysh8 as another parser abstraction stack.
- A literal Borg rebuild with production-shaped operational concerns.
- A naked game engine, parser framework, board-game engine, or simulation framework without one concrete world.

## Intent

I do not want to build production systems. I want to build small worlds. Worlds where simple rules create surprising behavior. Worlds where every interesting event has an understandable cause. Worlds that are fun to explore because they make complicated ideas feel tangible.

If someone walks away understanding computers, railroads, distributed systems, puzzles, games, scheduling, or language design a little better because they spent an hour inside one of those worlds, then I probably built the right thing.

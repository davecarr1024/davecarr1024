# Project Inventory

Last refreshed: 2026-07-10.

This inventory is based on the GitHub repositories owned by `davecarr1024`, plus local checkout context under `~/projects`. The GitHub pass used repository metadata, visibility, default branches, README files where present, design docs where present, and shallow top-level/tree inspection.

## Summary

The GitHub account currently contains 41 repositories:

- 13 public repositories.
- 28 private repositories.
- Several older private repos are experiments, stubs, or historical iterations.
- The largest project families are parser/language experiments, virtual-computer experiments, puzzle/constraint solvers, game/game-engine experiments, and the new root developer-record repo.

## Local Checkouts

These repos are currently checked out under `~/projects`:

| Repo | Description |
| --- | --- |
| `davecarr1024` | Root developer record for long-term planning, standards, agent guidance, and future project designs. |
| `doki` | Learning distributed key-value database with sharding, leader-based replication, quorum writes, recovery, and SQL roadmap. |
| `eastman` | Text-rendered RPG remake with a custom framebuffer renderer, scene graph, event system, and data-driven content. |
| `gbge` | Generic board-game engine experiment around boards, move enumeration, and players. |
| `henka` | TypeScript/Canvas bullet hell shooter where enemy waves evolve using a fitness signal based on player engagement. |
| `irata` | Vertically integrated 8-bit fantasy computer system with language, assembler, cartridge, and hardware simulation ideas. |
| `irata2` | C++20 cycle-accurate 8-bit CPU simulator with HDL, generated ISA, microcode, assembler, tests, and demos. |
| `pirata` | Python 6502-style cycle-accurate CPU simulator with customizable microcode and assembler pipeline. |
| `pysh6` | Python parser/language stack experiment combining regex, lexer, parser, interpreter layers, and tests. |
| `pysh7` | Later Python parser/language stack iteration with core errors, processor rules, streams, tokens, and parser infrastructure. |
| `rule_lab` | Completed C++23 typed-rule research proof with `Rule<State, Result>`, typed composition, lexer/parser sidecars, graph finalization, regex rebuild, and a tiny evaluated language. |
| `sudologue` | Proof-producing Sudoku solver that derives placements using logical deduction, not search. |
| `tracky` | Python virtual model railroad platform with grid track, car physics, projection math, and planned operations layers. |

## Public GitHub Repositories

| Repo | What it is |
| --- | --- |
| `davecarr1024/banana` | Python Bananagrams-style word-grid solver and search/constraint playground with pluggable constraints, search strategies, parameter tuning, and tests. |
| `davecarr1024/bitta` | CMake/C++ concept repo for an event-driven digital circuit simulator where logic emerges from node/drive interactions over time; docs cover primitives, traces, contracts, and a path toward flip-flops/CPU building. |
| `davecarr1024/davecarr1024` | Root developer record and planning repo. Holds project philosophy, coding standards, agent guidance, future project designs, and cross-project inventory. |
| `davecarr1024/doki` | Go learning distributed database with coordinator/nodes, shard placement, leader-based replication, quorum semantics, recovery, integration tests, and reliability-test ambitions. |
| `davecarr1024/eastman` | Python remake of an old personal text RPG, using deterministic simulation, a custom framebuffer text renderer, scene graph, event bubbling, and data-driven game content. |
| `davecarr1024/henka` | TypeScript/Vite/Vitest bullet hell shooter where waves evolve toward an engagement target using visible genetic adaptation and budgeted difficulty. |
| `davecarr1024/irata` | C++ 8-bit fantasy computer / retro platform exploring a custom language, assembly layer, cartridge format, interpreter, and signal-level simulation. |
| `davecarr1024/irata2` | C++20 cycle-accurate CPU simulator with strongly typed base types, HDL structure, generated ISA definitions, microcode DSL/IR, simulator, assembler, and GoogleTest coverage. |
| `davecarr1024/pirata` | Python IRATA successor: cycle-accurate educational 6502-style CPU simulator with microcode generation, assembler, strict typing, and co-located tests. |
| `davecarr1024/pysh6` | Public Python parser/interpreter experiment and cautionary stack: regex, lexer, parser framework, Pype/Pysh layers, and a deep abstraction chain. |
| `davecarr1024/sudologue` | Python Sudoku solver that never guesses. It derives axioms, eliminations, lemmas, and theorems so every placement has an inspectable proof. |
| `davecarr1024/sudoku` | Python generic CSP engine using Sudoku as the demonstration case. Includes constraint propagation, rollback/search support, and pluggable solver strategies. |
| `davecarr1024/tracky` | Python virtual model railroad platform for grid layouts, physically grounded train movement, switching puzzles, sandbox operation, and future automation/world layers. |

## Private GitHub Repositories

| Repo | What it appears to be |
| --- | --- |
| `davecarr1024/bcs` | Python computer simulator named `pycom`, with components such as ALU, bus, byte, clock, controller, memory, program counter, registers, instructions, operands, references, and tests. |
| `davecarr1024/cysh` | Empty/stub private repo with only `.gitignore` at the time of inspection. Likely a planned Cython/C-style shell or language experiment by name. |
| `davecarr1024/esh` | C# board-game/engine experiment with `Board`, `Piece`, `Position`, `Side`, and tests. Likely a C# counterpart to `ess`. |
| `davecarr1024/ess` | Python board-game/minimax experiment with board tree expansion, min-max players, text player, piece values, weighted random choice, and tests. |
| `davecarr1024/fge` | Empty/stub private repo with only `.gitignore` at the time of inspection. Likely a future game-engine experiment by name. |
| `davecarr1024/fhe` | Small Python foundational/game-engine experiment with node/visitor core and 2D math types (`vec2`, `mat2`, `rot2`) plus tests. |
| `davecarr1024/fhe2` | Larger Python FHE iteration with node/visitor/error/validation core, 2D/3D math, line/segment geometry, spatial nodes, clock/tick framework, and tests. |
| `davecarr1024/flip` | Python gate/computer simulation project with bytes/words, ALU operations, buses, registers, memory, controller, instruction memory, status register, stack pointer, and extensive tests. |
| `davecarr1024/gbge` | Private generic board-game engine experiment with board model, enumerators, game abstraction, and player abstraction. |
| `davecarr1024/libfhe` | Historical private import from `code.google.com/p/libfhe`. It contains many old subprojects including FHE variants, Sharpy/Sherp, Eastman, game-engine experiments, and assorted prototypes. |
| `davecarr1024/pint` | Empty private repo. |
| `davecarr1024/pyge` | Minimal Python game-engine stub with only `main.py`. |
| `davecarr1024/pysh` | Early Python language/parser experiment with regex, lexer, syntax, parser, loader, processor, `pysh.py`, and tests. |
| `davecarr1024/pysh2` | Python parser/language iteration with reusable core lexer/parser/processor plus `pysp` and `pysh` interpreter/value/type layers. |
| `davecarr1024/pysh3` | Python parser/language iteration with `core` lexer/parser/processor/stream infrastructure and a `pype` interpreter layer. |
| `davecarr1024/pysh4` | Python parser/language iteration with `core`, `pype`, and `pyte` layers, including classes, types, scopes, values, and tests. |
| `davecarr1024/pysh5` | Python parser/language iteration packaged under `pysh`, with core chars/errors/lexer/parser/regex/tokens and `pype` classes, expressions, functions, statements, and values. |
| `davecarr1024/pysh7` | Python parser/language iteration after `pysh6`, with core error, processor, stream, token, regex, lexer, parser, and related tests. |
| `davecarr1024/pysh8` | Near-empty private repo with only `.gitignore`. Likely a placeholder for another Pysh iteration. |
| `davecarr1024/pyshe` | Python parser framework/language experiment with chars, streams, errors, lexer, parser, regex, token streams, pyproject/uv/Replit setup, and tests. |
| `davecarr1024/pyshe2` | Later Python parser/processor experiment with chars, errors, processor combinators, regex state/result, streams, tokens, and tests. |
| `davecarr1024/rust` | Rust learning workspace containing small exercises/projects such as guessing game, hello world/cargo, mean, minigrep, and pig. |
| `davecarr1024/sharpy` | Early C# version of the parser/language stack with lexer, regex, parser, processor, syntax, and tests. |
| `davecarr1024/sharpy2` | Smaller C# processor/rule engine experiment with errors, refs, rules, processor state/results, and tests. |
| `davecarr1024/sharpy3` | C# parser/processor core with errors, n-ary/or/ref/rule/scope abstractions and tests. |
| `davecarr1024/sharpy4` | Larger C# parser stack with chars, containers, errors, lexer, parser results/rules/states, regex, tokens, and extensive tests. |
| `davecarr1024/shmips` | Empty private repo described as a C# computer simulator. |
| `davecarr1024/shype` | C# parser/language framework with chars, errors, lexer, parser combinators, regex, streams, tokens, and tests. |

## Project Families

### Root Developer Record

- `davecarr1024/davecarr1024`

This repo is the durable cross-project record: standards, planning, future designs, and the inventory itself.

### Virtual Computers And Digital Logic

- `bcs`
- `bitta`
- `flip`
- `irata`
- `irata2`
- `pirata`
- `shmips`

This family explores computers from several levels: gate/circuit simulation, component-level CPU simulation, microcode, assembly, generated ISA definitions, and fantasy-console/toolchain work.

### Parser, Language, And Shell Experiments

- `pysh`
- `pysh2`
- `pysh3`
- `pysh4`
- `pysh5`
- `pysh6`
- `pysh7`
- `pysh8`
- `pyshe`
- `pyshe2`
- `rule_lab`
- `sharpy`
- `sharpy2`
- `sharpy3`
- `sharpy4`
- `shype`
- `cysh`

This is the largest historical family. It contains repeated attempts at regex, lexer, parser, parser-combinator, processor/rule, interpreter, type/value, and shell/language infrastructure in Python and C#.

### Games, Game Engines, And Sim Worlds

- `eastman`
- `ess`
- `esh`
- `fge`
- `fhe`
- `fhe2`
- `gbge`
- `henka`
- `libfhe`
- `pyge`
- `tracky`

This family includes old and new game-engine experiments, board-game engines, an RPG remake, adaptive shooter, and model railroad/simulation work.

### Puzzle And Constraint Solvers

- `banana`
- `sudoku`
- `sudologue`

These repos focus on constraints, search, deduction, proof output, and solver architecture.

### Learning / Stubs / Historical Containers

- `pint`
- `rust`

`rust` is a Rust learning workspace. `pint` is empty. Some other repos above are also stubs, but they are grouped by apparent intended family.

## Newly Added To This Inventory

The previous inventory listed only a subset: `bitta`, `tracky`, `doki`, `sudologue`, `henka`, `irata2`, `irata`, `sudoku`, and `banana`, plus local checkouts.

Newly added in this refresh:

- `bcs`
- `cysh`
- `davecarr1024`
- `esh`
- `ess`
- `fge`
- `fhe`
- `fhe2`
- `flip`
- `gbge`
- `libfhe`
- `pint`
- `pirata`
- `pyge`
- `pysh`
- `pysh2`
- `pysh3`
- `pysh4`
- `pysh5`
- `pysh6`
- `pysh7`
- `pysh8`
- `pyshe`
- `pyshe2`
- `rust`
- `sharpy`
- `sharpy2`
- `sharpy3`
- `sharpy4`
- `shmips`
- `shype`

## Project Matrix

| Project | Core object | Primary themes | Best next question |
| --- | --- | --- | --- |
| Banana | Word-grid solver | Constraint propagation, search, tuning, dictionary rules | What reasoning output makes strategy differences obvious? |
| BCS | Python computer | Component-level CPU simulation, instructions, operands, tests | Which demo program proves the simulated machine is alive? |
| Bitta | Node / drive intent | Event-driven digital logic, trace contracts, emergent gates | Can a D flip-flop be proven from primitive node interactions? |
| Doki | Shard | Consistency, replication, leader assignment, recovery | What failure scenario should be easiest to understand visually? |
| Eastman | Text RPG scene | Deterministic game loop, scene graph, framebuffer rendering | What single memorable scene should define the game? |
| Flip | Gate/computer component | Gate-level CPU simulation, ALU, controller, instruction memory | What boundary separates useful CPU modeling from another full IRATA? |
| GBGE / ESS / ESH | Board | Board engines, move enumeration, min-max search, generic players | What single game should become delightful before extracting an engine? |
| Henka | Wave genome | Adaptive difficulty, bullet patterns, visible evolution | What does adaptation feel like to the player moment to moment? |
| IRATA | Virtual computer | Whole-stack retro computing, compiler and hardware simulation | What makes the fake console uniquely fun to program? |
| IRATA2 | C++ CPU platform | Strong typing, HDL, generated ISA, microcode, tests as proof | What future world deserves this level of stable layering? |
| PIRATA | Python CPU simulator | Cycle accuracy, assembler, microcode, testable hardware | What demo program proves the architecture is alive? |
| Pysh / Sharpy / Shype / Rule Lab family | Parser rule | Regex, lexer, parser, processors, interpreter layers, abstraction risk, typed-rule repair | What concrete proof artifact makes each layer safe to build on, and when is the research question answered enough to stop? |
| Sudologue | Proof | Logic, explainability, no guessing, formal derivation | Can the proof output teach a human a solving technique? |
| Sudoku | CSP model | Propagation, rollback, reusable puzzle modeling | When does reuse help more than one concrete puzzle? |
| Tracky | Track graph / car | Physical simulation, operations, sandbox, automation | What is the smallest railroad world that creates operational pressure? |

## Source Note

This refresh used:

- GitHub repo metadata from `gh api user/repos?affiliation=owner`.
- Top-level and shallow recursive repository tree inspection through the GitHub API.
- README files for public/current projects where available.
- Bitta concept/design/roadmap docs.
- Local checkout context for repos currently present under `~/projects`.

Descriptions for empty/stub repos are intentionally conservative.

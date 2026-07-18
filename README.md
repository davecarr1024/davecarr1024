# Dave Carr

I build small, deterministic worlds where hidden systems become visible.

My favorite projects are executable models: intentionally small versions of serious systems where simple rules create interesting behavior, every important state can be inspected, and every surprising event has an understandable cause.

I am less interested in building production systems than in building things that help me understand how systems work from the inside.

A high-level goal of my development practice is not being stuck: moving steadily by identifying the next bite-size piece, designing it, implementing it, verifying it, and delivering it as a stable building block. Agent-driven development is one of my main tools for preserving that flow while keeping design intent explicit.

## Developer Record

This repository is also my root developer record:

- `projects.md` tracks the active structure of this repo as a planning hub.
- `developer-record/project-philosophy.md` holds the long-form design philosophy and lessons from past projects.
- `developer-record/project-inventory.md` summarizes local and GitHub projects.
- `future-project-designs/` holds early project designs, including the Railroad Worlds and Paper Railroad docs.
- `train-book/` holds the raw OCR text and analysis fingerprint for *The American Railway*, the source lens behind the railroad-world ideas.
- `agents.md` and `CODING_STANDARDS.md` hold cross-repo agent and coding guidance.

Markdown is the standard documentation format. For normal project repos, the expected shape is a root `README.md`, a canonical `docs/design.md`, and optional detailed `docs/*.md` files.

For mature, revived, or idea-heavy projects, the explanation should separate
four jobs: `README.md` says what the project is and how to run it, `status.md`
shows what it can do now and why that is interesting,
`technical-description.md` explains how the machine works, and the tests provide
the executable evidence.

## Project Themes

### Virtual Computers

**IRATA**, **PIRATA**, and **IRATA2** are fake computers built from language design, assembly, microcode, HDL, simulation, tests, demos, and debug tooling.

The lesson I keep from this line of work is that layers are fun when each one earns the next:

```text
bits -> registers -> instructions -> assembly -> programs -> games
```

IRATA2 is my architectural gold standard: stable boundaries, generated sources of truth, strong types, validators, readable tests, debug surfaces, and a full test run that proves the system is coherent.

### Logic And Proof

**Sudologue**, **Sudoku**, and **Banana** explore constraint systems, search, propagation, rollback, and proof.

The satisfying part is not just finding an answer. The satisfying part is understanding why the answer is forced.

### Operations Worlds

**Tracky** is a model railroad project. It points at a broader interest in operational systems: dispatching, routing, load movement, scheduling, resource pressure, and local decisions creating global behavior.

I like systems where I can operate the world and watch the consequences.

### Games And Feedback Loops

**Eastman** and **Henka** are game-shaped projects with deterministic systems underneath: a text RPG and an adaptive shooter.

They remind me that a project needs something alive early. A dungeon room, a moving train, a proof, one replicated write, one rendered frame. That first runnable moment is not just a milestone. It is the fuel.

### Cautionary Projects

**Doki** was a distributed database that grew from a visible model into too many serious systems at once: replication, durability, leader election, sharding, operations, reliability, and SQL. I still like the problem space, but the project lost its explanatory center.

**Pysh6** was my tallest stack of parser/compiler abstractions: regex, lexer, parser framework, Lisp-ish interpreter, Python-ish interpreter, and the start of a C#-ish language. It was elegant, but changes eventually required too much vertical surgery.

The lesson from both: architecture should serve the world, not become the world.

## Design Principles

### Build Executable Models

I should prefer miniature worlds over utilities: a computer to inhabit, a railroad to operate, a cluster to watch, a puzzle universe to reason inside.

### Preserve Causality

Seeing what happened is not enough. I want the system to explain why it happened through proofs, traces, timelines, occupancy diagrams, state transitions, and readable diagnostics.

### Compress, Do Not Generalize

I want the smallest set of rules that generates rich behavior.

Good models compress. Generic frameworks often expand.

### Encode Truth Once

Every important fact should exist in one place. Documentation, visualizations, tests, diagnostics, and tools should derive from the model instead of becoming parallel descriptions.

### Make Invalid States Unrepresentable

I like strong representations because they make the world harder to misuse. When practical, the type system, generated definitions, validators, and structured data should encode the rules of the world.

### Tests Are The Deliverable

For my projects, the proof is the product.

A demo is nice, but the deeper pride is a full test run: every layer exercised, every invariant checked, every expansion covered, 100% pass, and coverage accounted for.

Readable tests matter. A good test should set up the world, perform the action, and assert the meaningful final state. If the test needs a thousand lines of boilerplate, mocks, and special cases, the representation is probably wrong.

### Earn The Next Layer

The next layer should feel inevitable, not magical.

V1 is allowed to be wrong. The healthy pattern is to build a concrete version, extract real design regrets, and let v2 be smaller and clearer. The dangerous loop is restarting before the current version has taught me something specific.

## What I Am Thinking About Next

The strongest current candidate is **Paper Railroad**: a discrete railroad economy inspired by the paper maps I made as a kid for my model train layout.

The first layer would be static:

- towns as nodes
- routes as edges
- goods as flows
- producers and consumers
- waybills as causal objects
- route capacity as the first resource constraint

No clock. No trains. No dispatcher at first.

Just a map analyzer that can answer:

- Is this economy balanced?
- Are all demands reachable?
- What transport bandwidth is required?
- Which routes are bottlenecks?
- If the railway works, can it be a going concern?

It has the load-and-balance flavor I like from schedulers, the operations flavor I like from railroads, and a personal hook that keeps it from becoming another production-shaped systems project.

Another future-project shelf item is **Spreadsheet Wars**: a naval operations analysis sandbox for studying salvo exchange, detection confidence, uncertainty, and decision delay as small probabilistic models. Its scope guardrail is to analyze the decision rather than simulate the battle.

## The Compass

I do not want to build production systems.

I want to build small worlds.

Worlds where simple rules create surprising behavior.

Worlds where every interesting event has an understandable cause.

Worlds that are fun to explore because they make complicated ideas feel tangible.

If someone walks away understanding computers, railroads, distributed systems, puzzles, games, scheduling, or language design a little better because they spent an hour inside one of those worlds, then I probably built the right thing.

# Dave Carr

I build small, deterministic worlds where hidden systems become visible.

My favorite projects are executable models: intentionally small versions of serious systems where simple rules create interesting behavior, every important state can be inspected, and every surprising event has an understandable cause.

I am less interested in building production systems than in building things that help me understand how systems work from the inside.

A high-level goal of my development practice is not being stuck: moving steadily by identifying the next bite-size piece, designing it, implementing it, verifying it, and delivering it as a stable building block. Agent-driven development is one of my main tools for preserving that flow while keeping design intent explicit.

## Start Here

This repository is the cross-project hub for five kinds of durable context:

- [Projects](projects.md) is the index of active, completed, historical, and
  candidate projects.
- [Developer record](developer-record/README.md) explains the recurring project
  philosophy and keeps portfolio-level synthesis.
- [Future project designs](future-project-designs/README.md) holds proposals
  that do not yet have an implementation repository and retained origin
  designs for projects that have been promoted.
- [Development and agent practice](agents.md) defines the cross-repo workflow;
  [coding standards](CODING_STANDARDS.md) supplies the default quality and
  language conventions.
- [Research](research/README.md) is reserved for findings that genuinely span
  multiple repositories. Project-specific research moves into that project's
  own `research/` directory.

The current project entry points include:

- [Barbacane](https://github.com/davecarr1024/barbacane), an executable siege
  engine for producing and explaining fortification plans from terrain,
  resources, period capabilities, and an adversary model;
- [Paper Railroad](https://github.com/davecarr1024/paper_railroad), an
  explainable railroad planning office built from circulation, capacity,
  economics, capital, and reliability evidence;
- [MoonRock](https://github.com/davecarr1024/moonrock), a preservation-led
  revival of an original DOS compiler through reproducible programs, captured
  frames, and project-owned recovery research;
- [Eastman 1](https://github.com/davecarr1024/eastman1), a deterministic
  QB64-PE reconstruction of a planned top-down kart game;
- [Rule Lab](https://github.com/davecarr1024/rule_lab) and
  [Game AI Lab](https://github.com/davecarr1024/game_ai_lab), completed v1
  research proofs whose docs record what their abstractions earned.

When entering an individual project, start with its `README.md`, then follow
its status/design links, technical description, project-specific research,
and executable tests. Each level should explain what was found, why it is
interesting, what currently runs, and where the evidence lives.

Markdown is the standard documentation format. New project repos start with a
root `README.md`, a canonical `docs/design.md`, and optional detailed
`docs/*.md` files. A mature project may split that design record into focused
documents when its README and local agent guide clearly map which file owns
each kind of truth.

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

### Adversarial Design

**Barbacane** treats fortification as an executable argument. The same ground
is reconsidered as weapons, construction, resources, and attacker behavior
change; each proposal must explain what attack it anticipates, how its works
support one another, and what happens when the enemy responds.

The long-term artifact is an illustrated chronicle derived from structured
evidence: plan, counterplan, partial information, actions, and consequences.
The first proof remains one small La Roche-Pont barbican study.

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

A demo is nice, but the deeper pride is a full proof run: every layer
exercised, every invariant checked, every expansion covered, and 100% pass.
Model-oriented projects also account for coverage; native visual and other
platform-bound projects document the artifact/runtime evidence that fits them.

Readable tests matter. A good test should set up the world, perform the action, and assert the meaningful final state. If the test needs a thousand lines of boilerplate, mocks, and special cases, the representation is probably wrong.

### Earn The Next Layer

The next layer should feel inevitable, not magical.

V1 is allowed to be wrong. The healthy pattern is to build a concrete version, extract real design regrets, and let v2 be smaller and clearer. The dangerous loop is restarting before the current version has taught me something specific.

## Current Work And Next Questions

**Paper Railroad** has moved from future design into an active, substantial
railroad-planning model. Its current work asks how capital, industry,
multi-commodity traffic, reliability shocks, and historical obligations can be
composed without hiding the baseline evidence.

**MoonRock** has also moved into a dedicated project. It asks how far the
original MoonRock 0.50 compiler can support deterministic DOS graphics and
small games when builds, generated assembly, framebuffer results, and captured
frames are made reproducible.

**Barbacane** is newly active. Its first work asks whether a simplified
La Roche-Pont barbican can prove and illustrate how an outwork changes an
attacker's sequence of access before the project attempts generated plans or a
simulated siege.

The future shelf remains useful, but promoted projects own their active design
and specific research. Strong unpromoted candidates include **Janney**,
**Tower**, **Compiler Lab**, and **Spreadsheet Wars**. The deciding question is
not which architecture sounds largest; it is which next small world can make a
hidden mechanism visible through a runnable artifact and readable proof.

## The Compass

I do not want to build production systems.

I want to build small worlds.

Worlds where simple rules create surprising behavior.

Worlds where every interesting event has an understandable cause.

Worlds that are fun to explore because they make complicated ideas feel tangible.

If someone walks away understanding computers, railroads, distributed systems,
puzzles, games, fortifications, scheduling, or language design a little better
because they spent an hour inside one of those worlds, then I probably built
the right thing.

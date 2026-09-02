# Projects

This repo is my root developer record: the place to keep long-term project planning, cross-project standards, reusable agent instructions, and early design notes that are not ready to become their own repositories.

The working rule is simple: this repository should remember the ideas, constraints, and standards that should survive across projects. Once a future design becomes an active project, its working design moves into that project's own `README.md`, `docs/design.md`, and local agent file.

Markdown is the documentation standard. New projects should start with a root
`README.md`, a canonical `docs/design.md`, and optional deeper `docs/*.md`
files. Mature projects may replace the single design file with a clearly
mapped set of authoritative documents when the split reflects real audiences
or responsibilities.

A high-level operating goal is not being stuck: use design discussion, agent-driven implementation, clear standards, bite-size work units, and verification to keep projects moving steadily from one stable building block to the next.

Idea-heavy projects also need a curated explanation of what has become visible.
Tests prove the claims, technical documentation explains the machine, and
`status.md` explains the project to a human through current capabilities,
canonical scenarios, representative output, surprising tradeoffs, limitations,
and the next interesting question.

## Current Compass

I build small, deterministic worlds where hidden systems become visible.

The projects that stay interesting usually have:

- one concrete world instead of a generic framework,
- one fundamental object that organizes the design,
- deterministic behavior that can be replayed,
- inspectable state and readable diagnostics,
- tests that prove the model instead of only checking output,
- a first runnable moment small enough to reach quickly.

## Repo Roles

- `README.md`: public-facing developer summary and philosophy.
- `projects.md`: active long-term planning index.
- `developer-record/`: durable project philosophy and inventory moved from loose root files.
- `research/`: findings that span multiple repositories; project-specific
  research belongs in the owning project's `research/` directory.
- `agents.md`: canonical cross-repo agent instructions.
- `AGENTS.md`: compatibility pointer for tooling that expects this filename.
- `CODING_STANDARDS.md`: synthesized language and tooling standards from checked-out repos.
- `future-project-designs/`: future proposals plus clearly labeled origin designs retained after promotion.
- [Paper Railroad's train-book study](https://github.com/davecarr1024/paper_railroad/tree/main/research/train_book):
  source provenance, OCR, analysis, and project-owned railroad lenses.
- `future-project-designs/railroad-worlds-origin.md`: original railroad-world
  sketch retained beside the refined design as source provenance.

## Developer Record

- `developer-record/project-philosophy.md`: long-form project philosophy and lessons from `projects.html`.
- `developer-record/project-inventory.md`: dated 2026-07-10 local/GitHub portfolio snapshot and project matrix.
- `developer-record/agent-enabled-development-process.md`: explicit agent-driven process from brainstorming through verified delivery.
- `developer-record/open-questions-and-next-steps.md`: historical 2026-07-10 planning snapshot that preserves promotion decisions and their rationale.
- `future-project-designs/paper-railroad.md`: retained origin design for the active Paper Railroad repo.
- `future-project-designs/janney.md`: detailed design for the coupler and switching project.
- `future-project-designs/tower.md`: detailed design for the interlocking and route-authority project.
- `future-project-designs/railroad-fit-analysis.md`: comparison of train-based ideas against the design and execution goals.
- `future-project-designs/train-book-alignment.md`: analysis of how the railroad-world designs can preserve the spirit, period, and technical texture of *The American Railway*.
- [Paper Railroad's train-book study](https://github.com/davecarr1024/paper_railroad/tree/main/research/train_book):
  raw text, fingerprint, themes, topic map, and design support for *The
  American Railway*.
- [Barbacane's Viollet-le-Duc study](https://github.com/davecarr1024/barbacane/tree/main/research/viollet_le_duc_fortification):
  source foundation for *Annals of a Fortress* and *Castles and Warfare in the
  Middle Ages*.
- `/home/davecarr1024/projects/barbacane`: active repo for an executable siege
  engineer that produces and explains fortification plans from terrain,
  resources, period capabilities, and an adversary model.
- `future-project-designs/nes-emulator.md`: future design for a transparent NES emulator, with fit analysis against the existing CPU-simulator history.
- `future-project-designs/compiler-lab.md`: future design for learning compiler fundamentals with an inspectable pipeline, TAC, and tiny execution environment.
- `future-project-designs/game-ai-lab.md`: retained origin design for the completed Game AI Lab v1.
- `/home/davecarr1024/projects/rule_lab`: active repo for a C++23 typed rule algebra that grows from pure rules to character-stream regex combinators.
- `future-project-designs/rule-lab.md`: retained origin design for the completed Rule Lab v1.
- `future-project-designs/typed-game-engine.md`: future design for a C++23 statically validated game object tree with typed properties, behaviors, and messages.
- `future-project-designs/symbolic-math-lab.md`: future design for a SymPy-like C++23 symbolic expression and rewrite system.

## Future Project Designs

The strongest current direction is a family of railroad-world projects. Paper
Railroad has been promoted and is active; Janney and Tower remain future
designs. These are related by philosophy, not necessarily shared code.

| Project | Core object | Question | First runnable moment |
| --- | --- | --- | --- |
| Janney | Coupler | How does it move? | One inglenook switching puzzle with slack, momentum, coupling, and uncoupling. |
| Tower | Route | When may it move? | One junction where every signal clear or denial has an inspectable safety explanation. |
| NES Emulator | Frame | Can a real console explain itself? | One simple NROM ROM produces a deterministic, asserted frame. |
| Compiler Lab | Program | Can compiler basics be learned through inspectable artifacts? | A tiny program compiles through tokens, AST, TAC, VM code, trace, and output. |
| Typed Game Engine | GameObject | Can C++23 types statically validate object properties, behaviors, and message plumbing? | One tiny object tree runs a deterministic frame after compile-time behavior/property checks. |
| Symbolic Math Lab | Expr | Can C++23 types make symbolic expressions, rewrites, and simplification traces explicit? | A tiny arithmetic expression simplifies through named rewrite rules with an inspectable trace. |
| Go Forth | Reachable adventure | Can a railway planner reveal interesting one-way possibilities from a traveler's current state rather than require a destination first? | From Kanazawa at 09:00, return several diverse, explainable railway days from a small baked network. |
| Spring Body Lab | ODE-driven material | Can a small deterministic laboratory make numerical integration, deformable materials, fracture, and structural failure visible and testable? | One spring compares several integrators against its analytic solution in a headless test and browser inspector. |
| Rigid Body Lab | Rigid pose and contact | Can a small deterministic laboratory make rotation, collision impulses, and joints understandable without recreating Bullet? | A falling circle collides with a floor and explains its normal, impulse, and changed state. |

See `future-project-designs/railroad-worlds.md` for the consolidated railroad-family design, the individual project design docs, `future-project-designs/railroad-fit-analysis.md` for the cross-project fit analysis, and [Paper Railroad's train-book study](https://github.com/davecarr1024/paper_railroad/tree/main/research/train_book) for the *American Railway* source-text fingerprint and cross-references.

See `future-project-designs/spring-body-lab.md` for the ODE-first deformable-material laboratory and its later 2D breach-game capstone.

See `future-project-designs/rigid-body-lab.md` for its rigid-body companion and their intentionally narrow shared ODE/math basis.

## Standards To Preserve Across Projects

- Start with one small, complete, inspectable world.
- Give every project a good name as part of the initial brainstorming process: short punchy proper-noun names for creative/releasable projects, descriptive names for labs and experiments.
- Use the agent-enabled development process: brainstorm, name, design, phase, execute, verify, and checkpoint.
- Treat every push as a code-and-design review boundary: run local evidence
  gates and a fresh-context self review, then use `agy` in read-only plan mode
  for an independent review of the final intended contents before pushing.
- Preserve not-being-stuck as a first-class goal: define the next bite, design it, implement it, verify it, and deliver it as a stable building block.
- Use Markdown for durable documentation.
- Give every project a root `README.md` and an explicit design record; use
  `docs/design.md` by default for new projects.
- Add `status.md` when a project needs a human-readable capability narrative.
- Add `technical-description.md` when a project needs a compact architecture and
  data-flow explanation.
- Keep detailed project docs under `docs/*.md`.
- Prefer a concrete model over an engine.
- Encode important truths once and derive docs, tests, diagrams, and diagnostics from that model where practical.
- Make invalid states unrepresentable when doing so clarifies the design.
- Treat tests as the proof of the world.
- Treat 100% production-code coverage as the standard goal for model-oriented
  code and a useful design signal. Native visual, platform, interactive, and
  recovered-binary projects should document an equivalent artifact/runtime
  evidence gate when coverage is not meaningful.
- Give every project a test or artifact-verification command and a
  presubmit/all-check command; model-oriented projects should also provide a
  coverage command.
- Write postmortems before rewrites. A v2 needs lessons from v1, not just imagined cleanliness.
- Keep administrative complexity out until the model itself has earned it.

## Parking Lot

- Add one design file per future project as the ideas become more concrete.
- Convert mature future designs into project repos when they are ready to implement, leaving behind origin notes or pointers here.

## Promoted Project Repos

| Project | Path | Status | Why it is interesting |
| --- | --- | --- | --- |
| Barbacane | `/home/davecarr1024/projects/barbacane` | Active inception | Val d'Ohet provides one evolving world in which an inspectable siege engineer can analyze and eventually generate fortification plans under changing constraints and weapons. |
| Paper Railroad | `/home/davecarr1024/projects/paper_railroad` | Active | An explainable planning office composes recurring circulation, economics, capital, industry, shared traffic, and reliability without collapsing their evidence. |
| MoonRock | `/home/davecarr1024/projects/moonrock` | Active | The recovered original compiler is used as a hard constraint for reproducible DOS graphics programs, tests, and captured artifacts. |
| Eastman 1 | `/home/davecarr1024/projects/eastman1` | Active reconstruction | A QB64-PE content and rendering lane reconstructs a planned kart game while keeping provenance and new work distinct. |
| Rule Lab | `/home/davecarr1024/projects/rule_lab` | V1 complete | One typed C++ rule model proved execution, diagnostics, lexer dependencies, graph structure, and a tiny language through the same inspectable object family. |
| Game AI Lab | `/home/davecarr1024/projects/game_ai_lab` | V1 complete | One generic match/search boundary plays Tic-Tac-Toe and Mini Connect Four and records what the second concrete game forced the abstraction to learn. |

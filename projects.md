# Projects

This repo is my root developer record: the place to keep long-term project planning, cross-project standards, reusable agent instructions, and early design notes that are not ready to become their own repositories.

The working rule is simple: this repository should remember the ideas, constraints, and standards that should survive across projects.

Markdown is the documentation standard. New projects should keep a root `README.md`, a canonical `docs/design.md`, and any deeper planning or architecture notes as optional `docs/*.md` files.

A high-level operating goal is not being stuck: use design discussion, agent-driven implementation, clear standards, bite-size work units, and verification to keep projects moving steadily from one stable building block to the next.

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
- `agents.md`: canonical cross-repo agent instructions.
- `AGENTS.md`: compatibility pointer for tooling that expects this filename.
- `CODING_STANDARDS.md`: synthesized language and tooling standards from checked-out repos.
- `future-project-designs/`: design shelf for project ideas I want to tinker with before they become repositories.
- `train_ideas.md`: original pulled railroad-world sketch kept as source material.

## Developer Record

- `developer-record/project-philosophy.md`: long-form project philosophy and lessons from `projects.html`.
- `developer-record/project-inventory.md`: local/GitHub project summary and project matrix from `PROJECT_SUMMARY.md` and `projects.html`.
- `future-project-designs/paper-railroad.md`: detailed design from `PAPER_RAILROAD_DESIGN.md`.
- `future-project-designs/janney.md`: detailed design for the coupler and switching project.
- `future-project-designs/tower.md`: detailed design for the interlocking and route-authority project.
- `future-project-designs/railroad-fit-analysis.md`: comparison of train-based ideas against the design and execution goals.
- `future-project-designs/nes-emulator.md`: future design for a transparent NES emulator, with fit analysis against the existing CPU-simulator history.
- `future-project-designs/compiler-lab.md`: future design for learning compiler fundamentals with an inspectable pipeline, TAC, and tiny execution environment.
- `future-project-designs/game-ai-lab.md`: future design for a generic board-game representation and AI system earned through concrete games.

## Future Project Designs

The strongest current direction is a family of railroad-world projects. These are related by philosophy, not necessarily shared code.

| Project | Core object | Question | First runnable moment |
| --- | --- | --- | --- |
| Paper Railroad | Waybill | What should move? | A static map analyzer that explains supply, demand, reachability, route load, and bottlenecks. |
| Janney | Coupler | How does it move? | One inglenook switching puzzle with slack, momentum, coupling, and uncoupling. |
| Tower | Route | When may it move? | One junction where every signal clear or denial has an inspectable safety explanation. |
| NES Emulator | Frame | Can a real console explain itself? | One simple NROM ROM produces a deterministic, asserted frame. |
| Compiler Lab | Program | Can compiler basics be learned through inspectable artifacts? | A tiny program compiles through tokens, AST, TAC, VM code, trace, and output. |
| Game AI Lab | GameState | Can one AI play many games through one interface? | One generic search policy plays two small deterministic games and explains moves. |

See `future-project-designs/railroad-worlds.md` for the consolidated railroad-family design, the individual project design docs, and `future-project-designs/railroad-fit-analysis.md` for the cross-project fit analysis.

## Standards To Preserve Across Projects

- Start with one small, complete, inspectable world.
- Preserve not-being-stuck as a first-class goal: define the next bite, design it, implement it, verify it, and deliver it as a stable building block.
- Use Markdown for durable documentation.
- Give every project a root `README.md` and `docs/design.md`.
- Keep detailed project docs under `docs/*.md`.
- Prefer a concrete model over an engine.
- Encode important truths once and derive docs, tests, diagrams, and diagnostics from that model where practical.
- Make invalid states unrepresentable when doing so clarifies the design.
- Treat tests as the proof of the world.
- Write postmortems before rewrites. A v2 needs lessons from v1, not just imagined cleanliness.
- Keep administrative complexity out until the model itself has earned it.

## Parking Lot

- Add one design file per future project as the ideas become more concrete.
- Decide whether mature design docs should stay here as canonical planning records or move into their project repos once implementation begins.

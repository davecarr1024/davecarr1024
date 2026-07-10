# Agent Guide

This is the root agent guide for my repositories. It is synthesized from the checked-out `CLAUDE.md`, `claude.md`, `pyproject.toml`, `CMakeLists.txt`, `Makefile`, `go.mod`, and `package.json` files under `~/projects`.

Use this file as the default when starting new repositories. If a project has its own `AGENTS.md`, `CLAUDE.md`, or `claude.md`, that project-local file wins for project-specific commands and invariants.

## Working Style

- Read the project `README.md`, `docs/design.md`, other relevant `docs/*.md`, and local agent file before changing code.
- Prefer the repo's existing patterns, commands, and abstractions over new ones.
- Keep work in small, focused steps that can be built, tested, and reviewed independently.
- Maintain the "not being stuck" loop: identify the next bite-size piece, define done, design it, implement it, verify it, and leave behind a stable building block.
- Do not implement future-phase concepts while working in the current phase.
- Preserve user changes. Never revert work you did not make unless explicitly asked.
- Keep commits focused when committing is requested. Do not force-push or force-commit.

## Project Philosophy

- Build small executable models before generic frameworks.
- Keep one concrete world at the center of the project.
- Prefer deterministic behavior, replayable tests, and inspectable state.
- Make causality visible through proofs, traces, diagnostics, timelines, or rendered state.
- Encode important truths once and derive docs, tests, generated code, diagnostics, and UI from that source where practical.
- Make invalid states unrepresentable when doing so clarifies the model.
- Add abstractions only after they earn their place.

## Quality Gates

Before calling a coding task done:

- The completed unit of work should have a clear role in the larger system.
- Run the project's full local check command when practical.
- Add or update tests for changed behavior.
- Keep coverage expectations intact. Several repos target 100% coverage for production code.
- Update docs, roadmaps, and local agent files when architecture, commands, phases, or behavior change.
- Report exactly which checks were run and which were not.

## Anti-Stuck Workflow

When work is ambiguous or broad:

- First shrink it to the next coherent sub-module.
- State the local design before editing code.
- Prefer a vertical slice that produces an inspectable artifact over a broad foundation with no proof.
- Verify the result before expanding scope.
- If the implementation starts spreading across too many concepts, stop and re-cut the work into a smaller step.
- Keep the user oriented enough that they can supervise the development process and understand each action being taken.

## Common Commands

Python projects usually use Poetry, Poe, Black, Ruff, Pyright strict mode, Pytest, and coverage:

```bash
poetry run poe all
poetry run poe format
poetry run poe lint
poetry run poe typecheck
poetry run poe test
```

C++ projects usually use CMake, CTest, GoogleTest, and optional coverage:

```bash
cmake -B build -DBUILD_TESTING=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure -j 8
```

Go projects usually use Make targets over direct commands:

```bash
make build
make test
make test-int
make lint
```

TypeScript projects usually use npm scripts:

```bash
npm test
npm run build
npm run dev
```

Always prefer the local repo's exact command if it differs from these defaults.

## Testing Expectations

- Tests should prove meaningful model behavior and invariants, not just line execution.
- Prefer readable fixtures, table-driven cases, and structured results.
- Use public interfaces where possible.
- Avoid mocking internal collaborators when real objects make a clearer test.
- Keep timing-sensitive tests deterministic. Use fake clocks, explicit synchronization, or generous wait helpers.
- Clean up servers, goroutines, windows, files, and other resources with the project's standard cleanup mechanism.

## Documentation Expectations

- Use Markdown for durable documentation.
- Every project should have a root `README.md`.
- Every project should have `docs/design.md` as its canonical design document.
- Put optional detailed docs under `docs/*.md`.
- Keep design docs and roadmaps synchronized with implementation.
- Mark milestones complete when implementation and tests are complete.
- Before a rewrite, write down what the previous version taught and why local repair is not enough.
- Record important invariants near the model that depends on them.
- Keep local agent files concise and link to `README.md` and `docs/design.md` for long-form context.

## Language Notes

See `CODING_STANDARDS.md` for detailed language and tooling conventions.

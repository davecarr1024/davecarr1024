# Coding Standards

These standards summarize the patterns already present across my checked-out repositories. Project-local configuration is authoritative when it differs.

## Universal Standards

- Markdown is the standard documentation format. Keep durable documentation in `.md` files.
- Give every project a good name during initial brainstorming. Creative/releasable projects should use short punchy proper-noun names; labs, experiments, and educational projects should use descriptive names.
- Keep behavior deterministic unless randomness is the explicit subject of the project.
- Model the domain directly. Avoid generic engines before one complete concrete experience exists.
- Optimize for not being stuck: choose bite-size units of work with explicit design, verification, and delivery criteria.
- Prefer small, composable types with clear invariants.
- Prefer immutability by default. Make values, members, and helper functions
  `const`, frozen, readonly, or `static` when the language supports it and no
  mutation is intended. Treat mutation as an explicit design choice.
- Return or raise context-rich errors. Do not swallow failures.
- Keep generated artifacts derived from their source definitions.
- Comments should explain non-obvious logic, design decisions, invariants, and
  tradeoffs, not restate code. Add file-level or class-level comments when an
  abstraction's role would otherwise be ambiguous to a fresh reader.
- Add explanatory comments to classes and non-trivial methods when their role,
  invariants, tradeoffs, or failure behavior would not be obvious to a fresh
  reader. When a source file grows broad enough that comments are compensating
  for mixed responsibilities, split it into focused module files and group
  related concepts/classes under matching directories and namespaces where
  practical.
- Keep docs, roadmaps, and tests current with behavior changes.
- Treat 100% production-code coverage as the standard goal for model-oriented
  code. Thoroughly testable code is a good sign that the project is stable and
  well-shaped.
- Model-oriented projects should provide a coverage command; every project
  should provide a presubmit/all-check command that enforces its meaningful
  tests or executable artifact checks.
- For multi-module projects, group code by domain/module using directories and matching namespaces/packages. Prefer `module/submodule` layout over flat file lists once a second cohesive area appears.
- When a second concrete implementation forces a generic core, keep domain-friendly wrapper APIs around that core so callers can still speak the local model.
- Defer optional interfaces, evaluators, and strategy hooks until a concrete use case proves they are needed.
- A roadmap or major phase is not done until the presubmit command, a coverage
  gate for model-oriented code (or a documented alternate evidence gate),
  documentation updates, fresh-context self review, Gemini CLI review request
  when available, commit, and push all succeed.
- If external review tooling is unavailable, report that explicitly. Use pasted
  user-provided external review as advisory input when present, without claiming
  a tool review ran.
- Prefer local pre-commit hooks plus CI for the same checks. The hook catches mistakes before commit; CI proves the same workflow from a clean checkout.

## Unit Of Work Standard

A good unit of work should be:

- small enough to complete in one focused pass,
- specific enough to design before coding,
- testable through public behavior, structured diagnostics, or an inspectable artifact,
- complete enough to become a dependency for later work,
- documented when it changes the model, roadmap, commands, or standards.

Avoid units of work that are only "set up architecture" without a runnable proof. If a task cannot be verified, shrink or reshape it until it can.

## Agent-Enabled Project Process

New projects and major phases should follow the process in `developer-record/agent-enabled-development-process.md`:

1. Brainstorm and discuss the seed question.
2. Choose a good name.
3. Write the initial design.
4. Plan phases, deliverables, and checkpoints.
5. Execute a bite-size unit of work.
6. Verify with tests, checks, or inspectable artifacts.
7. Record lessons and next steps.

This process is part of the quality standard. A phase is not complete until its deliverable is verified and the relevant Markdown docs reflect the current model.

## Testing And Coverage Philosophy

The default testing goal is 100% production-code coverage.

This is not only a metric. It is a design smell and a design signal:

- If code is straightforward to cover thoroughly, the model is probably well-factored and inspectable.
- If coverage is painful, the code may be mixing responsibilities, hiding state, depending on incidental timing, or lacking useful public artifacts.
- If a line is intentionally excluded from coverage, the reason should be narrow and documented.

Every model-oriented project should have:

- a normal test command,
- a coverage command or coverage-producing test target,
- a formatting check when the language ecosystem has a standard formatter,
- a static-analysis or lint check when the ecosystem has a practical tool,
- a presubmit/all-check command that enforces formatting, static analysis or linting, and tests,
- coverage enforcement once the project is mature enough for it.

Projects centered on native visual runtimes, platform glue, interactive
artifacts, or recovered binaries should instead document the strongest
repeatable artifact and runtime checks their ecosystem supports.

For model projects, tests should prove behavior, invariants, diagnostics, traces, and generated artifacts. Line coverage is the floor, not the purpose.
When a status document uses canonical scenarios as a capability tour, promote
representative scenarios into executable tests so docs do not become unsupported
claims.

For boundary refactors, prefer a validated state boundary and explicit
compatibility adapters over an all-at-once rewrite. Document which adapters
remain and what debt they intentionally preserve.

When 100% coverage is not practical for a project area, document the exception in the local design or agent file. Common exceptions might include visual renderers, interactive shells, development scripts, or platform glue.

## Documentation Layout

Every project should have a small, predictable documentation structure:

- `README.md`: root project introduction, quick start, status, and links to deeper docs.
- `docs/design.md`: the default canonical design document for a new project.
- `docs/*.md`: optional detailed docs for architecture notes, roadmaps, protocols, milestones, feature designs, postmortems, and operating notes.
- `status.md` for mature, revived, or idea-heavy projects: a readable
  capability narrative showing what the system can do now and why that is
  interesting.
- `technical-description.md` for mature, revived, or architecture-heavy
  projects: a machine explanation covering architecture, data flow, boundaries,
  algorithms, and design decisions.
- `AGENTS.md` or `agents.md`: agent guidance when the project needs instructions beyond the root defaults.

Documentation rules:

- Prefer Markdown for all durable docs. Avoid HTML or ad hoc document formats for planning and design records.
- Include the project name and naming rationale in early design notes when the project is still forming, including whether it is a proper-noun creative project or a descriptive lab/experiment.
- When a future design becomes an active project, move the active design into
  that project's `docs/design.md` as part of repo creation.
- A mature project may divide the canonical design record among focused files
  when the split serves distinct audiences or responsibilities. Its README and
  local agent guide must map those files, name what each one owns, and prevent
  the same fact from becoming independently authoritative in multiple places.
- Keep the root `README.md` concise. Move detailed design material into `docs/design.md` or focused `docs/*.md` files.
- Keep the canonical design record current with the model that actually exists.
- Link detailed docs from `README.md` so a new reader can find the shape of the project quickly.
- Use `status.md` to preserve the project's thesis, canonical scenarios,
  representative output, surprising tradeoffs, current limitations, and next
  interesting question.
- Use `technical-description.md` when a fresh reader needs a compact map of how
  the implementation works before safely changing it.
- When a project has phases or milestones, keep the roadmap in `docs/roadmap.md` or inside `docs/design.md`, not scattered through implementation notes.
- Capture rewrite reasons and v1 lessons in a `docs/postmortem*.md` or design-history doc before starting a v2.

## Python

Observed repos: `eastman`, `pirata`, `tracky`, `sudologue`.

Default toolchain:

- Poetry for environments and packaging.
- Poe for task aliases.
- Black for formatting.
- Ruff for linting and import ordering.
- Pyright in strict mode.
- Pytest, pytest-cov, pytest-subtests, and often pytest-xdist.

Default command:

```bash
poetry run poe all
```

Style:

- Use type annotations throughout.
- Prefer `X | None` over bare `Optional`.
- Use frozen dataclasses for immutable value types.
- Use `typing.Protocol` for interfaces.
- Prefer `match`/`case` for state-machine or typed dispatch when it improves clarity.
- Keep tests near source when that is the repo's pattern, such as `component.py` beside `component_test.py`.
- Use `pytest.approx()` for floating-point checks.
- Use subtests for readable table-driven cases.
- Exclude interactive renderers, scripts, protocols, and dev-only helpers from coverage only when the project already treats them as coverage exceptions.

Coverage:

- Treat 100% production-code coverage as the default goal for Python model projects.
- Do not reduce coverage expectations to make a change pass.

## C++

Observed repo: `irata2`.

Default toolchain:

- CMake 3.20+.
- C++20.
- GoogleTest.
- CTest.
- `clang-format` for formatting.
- `clang-tidy` for static analysis when it can run cleanly over the project.
- Coverage via `ENABLE_COVERAGE=ON` once tests exist.

Default commands:

```bash
cmake -B build -DBUILD_TESTING=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure -j 8
```

Style:

- Keep module dependencies explicit and acyclic.
- Represent nested modules with subdirectories and matching namespaces, such as `include/project/game/rules.h`, `src/game/rules.cpp`, and `project::game`.
- Free functions are acceptable for cohesive domain operations, but put them in the domain namespace rather than the root project namespace.
- Let generated definitions come from source data such as YAML.
- Prefer strong types for domain values.
- Keep runtime state separate from immutable structure when the model benefits from that distinction.
- Keep compile warnings clean under `-Wall -Wextra -Wpedantic`.
- Keep `clang-format` and `clang-tidy` clean when the project has adopted them.
- Add focused GoogleTest coverage for new behavior.

## Go

Observed repo: `doki`.

Default commands:

```bash
make build
make test
make test-int
make lint
```

Style:

- Wrap errors with context using `%w`.
- Keep user-facing errors distinguishable from internal errors.
- Use injected interfaces for time, storage, clients, and other external dependencies.
- Use `context.Context` for background goroutines and shut them down cleanly.
- Do not hold multiple shard or model locks unless the local design explicitly allows it.
- Use `t.Cleanup()` for test resources, especially inside loops.
- Keep integration and reliability tests separated by tags when the project does.

## TypeScript

Observed repo: `henka`.

Default commands:

```bash
npm test
npm run build
npm run dev
```

Style:

- Keep core game logic testable without the browser.
- Separate simulation state, input, rendering, and evolution logic.
- Use Vitest for unit and integration tests.
- Make adaptive or generated behavior visible and inspectable rather than hidden.
- Keep mobile and desktop interaction constraints in mind when the project targets both.

## Build And Config Files

- Prefer existing task runners over ad hoc commands.
- Do not edit lockfiles, generated code, or build output unless that is part of the requested task.
- Do not introduce a new formatter, linter, package manager, or build system without a project-level reason.
- If a repo has a Makefile, Poe task, npm script, or CMake target for an operation, use that target.

## Agent File Conventions

- New repos should include a root `AGENTS.md` or `agents.md`.
- A project-local agent file should include:
  - project overview,
  - essential commands,
  - architecture map,
  - key invariants,
  - code conventions,
  - testing requirements,
  - documentation update rules,
  - current phase or roadmap pointer,
  - pointer back to `~/projects/davecarr1024` as the root developer rules dir,
  - instruction to promote reusable workflow, style, tooling, and process findings back to `~/projects/davecarr1024`.
- Agent files should point to `README.md` and the canonical design record
  rather than duplicating long design content.
- Keep local agent files concise enough to read before work starts.

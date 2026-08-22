# Agent-Enabled Development Process

This is the preferred project process for building with agents while preserving design control, forward motion, and implementation quality.

The goal is not to outsource judgment. The goal is to stay unstuck: discuss the design clearly, choose the next bite-size piece of work, implement it with supervision, verify it, and leave behind a stable building block.

## Final Goal

Each project should become a small deterministic world that is:

- named clearly,
- designed around one core question,
- organized around one fundamental object,
- split into phases with explicit deliverables,
- implemented in small verified increments,
- documented in Markdown,
- explained through a human-readable capability narrative when its central idea
  is not obvious from the code or category label,
- useful as a foundation for the next layer.

The end state of a phase is not "some code exists." The end state is a complete sub-module with tests, docs, and an inspectable artifact that proves what was built.

## Process Overview

The standard loop is:

1. Brainstorm and discuss the idea.
2. Find a good name.
3. Write the initial design.
4. Create or promote the project repo when the idea is ready to implement.
5. Plan phases, deliverables, and checkpoints.
6. Execute one bite-size unit at a time.
7. Verify each unit before expanding scope.
8. Record lessons, regrets, and next steps.

This process should be explicit at project start and repeated at each major phase boundary.

## 1. Brainstorming And Discussion

Brainstorming should identify the seed question, not just a category of software.

Good prompts:

- What hidden system do I want to make visible?
- What is the smallest world that captures the interesting part?
- What would be delightful to inspect, operate, or understand?
- What previous project does this continue or repair?
- What historical failure mode could this repeat?
- What should be out of scope even if it is tempting?

The output of brainstorming should be a short project thesis, not an architecture.

## 2. Naming

Every project needs a good name as part of initial brainstorming.

The name should help clarify the project. Good names usually come from:

- the fundamental object,
- the project fantasy,
- a historical reference,
- the personal hook,
- the visible artifact,
- the main operation the user performs.

There are two naming modes, chosen by project type:

- Proper-noun creative/releasable project: use a short, punchy, often punny name, such as `pysh`, `fge`, `IRATA`, `Henka`, or `Sudologue`.
- Experiment, lab, or educational project: use a descriptive name, such as `compiler_lab` or `game_ai_lab`.

The choice should be part of the design discussion. Creative projects benefit from identity and energy. Labs and experiments benefit from being immediately legible.

A weak placeholder is acceptable for a short time, but a project should not start implementation until the name is good enough to carry the idea.

Naming questions:

- Is the name short enough to remember?
- Does it point at this project rather than a generic category?
- Does it make the project easier to talk about?
- Does it imply a useful scope boundary?
- Would the name still fit the v1 first runnable moment?
- Is this a proper-noun creative/releasable project, or a lab/experiment/educational project?

## 3. Initial Design

The initial design should become `docs/design.md` once the project has a repo. While the idea is still forming, it can live in `future-project-designs/`.

The design should answer:

- What is the core question?
- What is the fantasy or point of view?
- What is the fundamental object?
- What is the first runnable moment?
- What is explicitly out of scope for v1?
- What are the main model objects?
- What must be deterministic and inspectable?
- What proves the model is working?
- What old failure mode is most likely?

The design should be specific enough to guide implementation but not so large that it blocks the first runnable artifact.

## 3.5. Post-Design Review

After a substantial design rewrite, roadmap reset, or major phase-plan change,
run a dual design review before treating the design as ready for
implementation.

The review has two parts:

- local deep review by the current agent,
- external review with Gemini CLI when available.

The local review should check:

- whether the design preserves the project thesis,
- whether the central abstraction is named clearly,
- whether phase gates are concrete and verifiable,
- whether implementation order matches dependency order,
- whether old assumptions or stale phase text contradict the new direction,
- whether open questions are captured instead of hidden inside prose,
- whether the next implementation checkpoint is small enough to test.

The Gemini review should be asked to focus on:

- contradictions,
- unclear abstractions,
- missing phase gates,
- weak terminology,
- implementation traps,
- open questions.

After both reviews:

- implement obvious documentation fixes,
- update `docs/design.md`, `docs/roadmap.md`, and project-local agent guidance
  as needed,
- capture unresolved conceptual questions explicitly,
- do not start broad implementation until the revised docs can be used as the
  source of truth.

This is not a replacement for judgment. It is a pressure test for whether the
design has become internally coherent enough to guide the next bite-size
implementation step.

The same review discipline applies at the end of each completed implementation
phase. The phase-close review should include both a fresh-context self review
and, when available, a Gemini CLI review of code and design together.

## 4. Repo Creation And Design Promotion

`davecarr1024` is the root developer record. It should hold developer-wide structure, reusable patterns, standards, agent process, inventory, and future designs.

When an idea moves from future design to active project, promote it into its own repo. That promotion should happen after the initial design discussion and naming, and before implementation work begins.

Project creation should produce:

- a repo with the chosen project name,
- a root `README.md`,
- `docs/design.md` containing the active project design,
- optional `docs/roadmap.md` for phases and milestones,
- project-local `AGENTS.md` or `agents.md` when the root guidance is not enough,
- initial commands and verification expectations.

After promotion, the active design source lives in the project repo beside the implementation. The original future-design file in `davecarr1024` can remain as an origin note or be replaced with a short pointer to the new repo.

Cross-project lessons, postmortems, reusable standards, and changes to the agent-enabled process should come back into `davecarr1024`.

## 5. Phases, Deliverables, And Checkpoints

Each project should be split into phases. A phase should produce a stable artifact, not just infrastructure.

A good phase has:

- one purpose,
- one or two central model changes,
- a concrete deliverable,
- tests or checks that prove it,
- docs updated to match,
- a checkpoint question before moving on.

Example phase shape:

```text
Phase: Static Map Validation
Deliverable: one map file can be loaded and rejected with structured diagnostics.
Verification: validation tests for unknown towns, unknown goods, disconnected routes, and invalid quantities.
Checkpoint: is the map representation clear enough to support waybills?
```

Avoid phases named only for architecture, setup, or framework work. If a phase cannot be verified, shrink it until it can.

## 6. Execution Loop

The execution loop for each unit of work is:

1. Define the next bite.
2. Define done.
3. State the local design.
4. Implement the change.
5. Run the relevant verification.
6. Update docs when behavior, architecture, commands, or phase state changed.
7. Summarize what changed and what the next bite should be.

Agents should keep the user oriented during this loop. The user should be able to understand why each action is being taken and how it moves the project toward the current phase deliverable.

## 7. Verification Steps

Verification is part of the deliverable.

Preferred verification methods:

- unit tests for model behavior,
- integration tests for complete flows,
- coverage runs for production code,
- golden outputs for generated artifacts,
- structured diagnostics that can be asserted directly,
- deterministic replay tests,
- command-line checks from the project task runner,
- screenshots or visual checks only when the experience requires them.

Verification should answer:

- Did the model behavior change as intended?
- Are important invalid states rejected?
- Is the result deterministic?
- Is the artifact inspectable?
- Is the code thoroughly testable, with 100% production-code coverage as the default goal?
- Did docs and tests stay synchronized with behavior?

For these projects, tests are not a cleanup step. The proof is the product.

Every project should define a presubmit or all-check command. At minimum it
should enforce its meaningful tests or executable artifact checks. Mature
model-oriented projects should also enforce coverage, with 100% production-code
coverage as the standard goal unless a narrow exception is documented; native
visual, platform, interactive, and recovered-binary projects should document
their strongest substitute evidence.

The preferred mature-project verification stack is:

- a formatter check,
- a static-analysis or lint check,
- tests,
- a coverage gate for model-oriented code, or a documented artifact/runtime
  evidence gate for other project types,
- a local pre-commit hook that runs the same checks,
- CI that runs the same checks from a clean checkout.

When a status document uses canonical scenarios to explain capabilities, promote
representative scenarios into executable tests. The status narrative should not
claim behavior that is only demonstrated in prose.

## 8. Phase Completion

A roadmap or major phase is complete when:

- the deliverable exists,
- tests or checks pass,
- documentation reflects the current model,
- `status.md` or the equivalent project status section explains what the system
  can do now, what proves it, what is surprising, and what remains limited,
- technical documentation explains architecture, data flow, boundaries,
  algorithms, and design decisions when the implementation is substantial
  enough to need that map,
- known gaps are written down,
- the current agent performs a fresh-context self review of the code against
  the design, the design against the project goals, and both against the root
  development principles,
- Gemini CLI is asked for an external code and design review when available,
  focused on whether the implementation follows the design and whether the
  design still serves the project principles, goals, and rules,
- if Gemini CLI or another external reviewer is unavailable, the phase record
  says so explicitly; pasted user-provided external review can be used as
  review input, but agents should not imply that a tool review ran,
- obviously correct review findings are implemented,
- review findings that are open questions, tradeoffs, or design choices are
  surfaced to the user for discussion before moving to the next phase,
- the completed phase is committed,
- the commit is pushed to the project remote when one exists,
- the next phase can build on the result without re-explaining it from scratch.

Before leaving a phase, write a short checkpoint note:

- What did this phase make visible?
- What surprised me?
- What became load-bearing?
- What should not be generalized yet?
- What is the next smallest useful phase?

For boundary refactors, prefer a validated state boundary plus explicit
compatibility adapters over a full rewrite. The phase should prove where raw
input enters, where trusted or validated state begins, which adapters still
exist, and which follow-up debt remains.

## 9. Returning To Older Projects

Returning to an older project is a second-edition exercise, not only
maintenance. Before adding broad new capability:

1. Recover the thesis.
2. Identify the fundamental objects.
3. Make the system's point of view explicit.
4. Inventory what the existing tests already prove.
5. Build or refresh the human-readable capability narrative.
6. Choose the next phase that deepens the central idea.

The durable artifacts should answer four different reader questions:

```text
README.md
  What is this, and how do I run it?

status.md
  What can it do now, and why is that interesting?

technical-description.md
  How does it work?

tests
  What executable evidence proves the claims?
```

## Agent Responsibilities

Agents should:

- preserve the project thesis and current phase boundary,
- challenge scope creep when it threatens the first runnable artifact,
- keep work in bite-size verified units,
- use project-local commands and conventions,
- update Markdown docs with design or process changes,
- report verification clearly,
- avoid future-phase implementation unless explicitly requested.

Agents should not:

- turn a concrete world into a generic framework prematurely,
- erase domain-friendly APIs just because a generic core has emerged,
- hide design choices inside unreviewed implementation,
- skip tests because a demo appears to work,
- continue broad implementation after the phase boundary becomes unclear,
- rewrite working code without a written reason.

## Project Start Checklist

Before implementation starts, the project should have:

- a good project name,
- a root `README.md`,
- `docs/design.md`,
- a v1 thesis,
- a phase plan,
- a first runnable moment,
- explicit non-goals,
- a verification strategy,
- planned test, coverage, and presubmit commands,
- project-local `AGENTS.md` or `agents.md` if the root guide is not enough.

## Default First Milestone

The default first milestone should be the smallest artifact that proves the project is alive:

- one map analysis,
- one route proof,
- one switching move,
- one frame,
- one compiled program,
- one AI match,
- one proof chain,
- one replicated write.

The artifact should be small, but it should be real. It should make the next step easier because a stable piece of the world now exists.

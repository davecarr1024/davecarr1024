# Railroad Worlds Fit Analysis

This compares the three train-based project ideas against the stated developer-record goals and the source lens in [Paper Railroad's train-book study](https://github.com/davecarr1024/paper_railroad/tree/main/research/train_book).

The railroad ideas are deliberately inspired by *The American Railway*. The book-derived analysis lives in:

- [fingerprint](https://github.com/davecarr1024/paper_railroad/blob/main/research/train_book/fingerprint.md)
- [themes](https://github.com/davecarr1024/paper_railroad/blob/main/research/train_book/themes.md)
- [cross-reference](https://github.com/davecarr1024/paper_railroad/blob/main/research/train_book/cross-reference.md)
- `train-book-alignment.md`

This comparison asks whether each project preserves the book's spirit in a small executable world rather than trying to model the entire book at once.

- small deterministic worlds,
- one fundamental object,
- causality and explanation,
- tests as proof,
- fast first runnable moment,
- concrete model before generic framework,
- personal hook,
- manageable execution risk.

## Summary Ranking

| Rank | Project | Fit | Why |
| --- | --- | --- | --- |
| 1 | Paper Railroad | Best first project | It can start as a static analyzer with no UI, no physics, no clock, and a naturally testable proof suite. |
| 2 | Tower | Best proof-as-game project | It has extremely strong causality and testing fit, but needs a visible panel or interaction surface earlier. |
| 3 | Janney | Best tactile/playable project | It may become the most immediately fun, but physical feel and tuning make execution risk higher. |

This ranking is about what should come first, not which idea is most valuable.

## Goal Matrix

| Goal | Paper Railroad | Janney | Tower |
| --- | --- | --- | --- |
| Small deterministic world | Strong | Strong | Strong |
| One fundamental object | Waybill | Coupler | Route |
| Causality | Strong | Medium to strong | Very strong |
| Tests as proof | Strong | Medium | Very strong |
| First runnable moment | CLI analyzer | Interactive switching | Route denial/clear panel |
| Main execution risk | Abstract logistics drift | Physics feel and tuning | UI clarity and signal-scope creep |
| Main scope trap | Economy/accounting realism | Layout editor and physics engine | Full signaling/dispatching system |
| Personal hook | Strongest | Strong | Medium to strong |
| Best implementation style | Headless model first | Headless physics plus minimal renderer | Data-driven rule table plus minimal panel |
| Train-book center | Way-bills, freight, records, civil route burden | Couplers, cars, brakes, mechanical events | Signals, switches, interlocking, route authority |

## Individual Fit Notes

### Paper Railroad

Paper Railroad is the most aligned with the current developer record. It has a clear non-UI first version and can produce satisfaction through proof:

- invalid maps fail with good diagnostics,
- valid maps produce waybills,
- waybills explain route load,
- route load explains bottlenecks,
- tests can cover the entire world.

The central risk is over-generalization. The project should remain a paper railroad, not a logistics solver in railroad clothing.

Train-book import priority:

- way-bill reports,
- route-load statistics,
- civil route burden,
- car-accounting vocabulary later.

### Janney

Janney is the most tactile and game-like. It has a concrete first scene and a strong central object, but the success criterion includes feel. That makes it harder to prove complete through tests.

It is a good candidate after either Paper Railroad or Tower because those projects can establish the discipline of railroad-world modeling before Janney demands tuning and interaction work.

The central risk is building a physics/layout engine instead of one satisfying inglenook.

Train-book import priority:

- structured coupling events,
- named cars and car classes,
- simple braking states,
- mechanical explanations for failed moves.

### Tower

Tower is the cleanest proof game. Its route table, locking, conflict, occupancy, and denial logic map directly to deterministic tests and causal explanations.

It probably wants a minimal UI earlier than Paper Railroad, because the core delight is seeing a plant state and understanding why a signal clears or refuses. That UI can still be simple and model-derived.

The central risk is importing too much real-world signaling detail too early.

Train-book import priority:

- route-denial taxonomy,
- fail-safe signal defaults,
- switch/lock/occupancy proof,
- period terms only when they map to model state.

## Recommended Sequence

### Step 1: Build Paper Railroad V1

Build the static analyzer first. It has the smallest dependency surface and the strongest path to a complete proof suite.

Success criterion:

- one map file,
- one CLI command,
- one readable explanation,
- tests for valid and invalid worlds,
- one documented design regret.

### Step 2: Choose Based On Desired Energy

After Paper Railroad V1, choose the next railroad project by what kind of work sounds energizing:

- Choose Tower if the appealing part is formal causality, route proof, and readable denial diagnostics.
- Choose Janney if the appealing part is direct manipulation, visual feedback, and physical play.

### Step 3: Keep The Projects Separate

Do not merge the codebases early.

The projects should share vocabulary and design philosophy, not infrastructure. Shared code should be extracted only after two projects have independently proven the same abstraction is real.

## Execution Standards For All Three

- Create a project repo with root `README.md` and `docs/design.md`.
- Keep the v1 design smaller than the interesting future vision.
- Build the headless model before the UI where practical.
- Make every important decision produce structured output.
- Cross-reference [Paper Railroad's train-book study](https://github.com/davecarr1024/paper_railroad/tree/main/research/train_book) when importing period vocabulary or technical detail.
- Import book details only when they become rules, diagnostics, tests, or reports.
- Write tests against model state and diagnostics.
- Add visual/manual tests only where the experience genuinely needs them.
- Write a v1 postmortem before starting a v2 or merging concepts across projects.

## Decision

Paper Railroad should remain the lead candidate.

Tower is the best second candidate if the goal is maximum alignment with proof, invariants, and explanation.

Janney is the best second candidate if the goal is maximum playable delight and Tracky continuity, with the understanding that it carries the highest tuning risk.

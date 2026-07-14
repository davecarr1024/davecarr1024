# Tower Design Doc

## Train Book Lens

Tower is explicitly inspired by *The American Railway*, especially `Safety in Railroad Travel` and the management material on dispatching, signals, blocks, and interlocked switches.

Primary cross-references:

- `../train-book/themes.md`: themes 6, 7, 8, 9, and 10.
- `../train-book/cross-reference.md`: `Tower`.
- `../train-book/fingerprint.md`: term clusters for signals, switches, interlocking, blocks, brakes, and telegraph.
- `train-book-alignment.md`: `Safety And Authority Lens`.

The book-derived rule for this project is: route authority is a proof under constraints. A signal should clear only because switches, locks, occupancy, and conflicts have all been checked. A denial is a successful explanation.

## Core Question

How do interlockings make railroads safe?

Tower is a small model of authority. The player does not drive trains, optimize an economy, or physically switch cars. The player establishes safe routes through a constrained plant. The interesting question is not "how fast can I click?" It is "why may this train move, and why may that one not move?"

## Fantasy

I am standing in a control tower overlooking an interlocking.

I do not tell engineers how to operate their trains. I do not move freight. I do not design the whole railroad. I manage the safety constraints that allow train movements to happen without conflict.

My work is proof work:

- line switches,
- lock points,
- request a route,
- clear a signal,
- watch occupancy,
- understand why a signal refuses to clear,
- release the route when the movement is complete.

## Fundamental Object

`Route`.

The route is the proof. A cleared signal means the system has demonstrated a safe path through the plant under the current switch, lock, occupancy, and conflict conditions.

Everything should support route proof:

- track circuits,
- switch detection,
- lock state,
- signal aspects,
- conflicting routes,
- approach locking,
- route release,
- explanations for denial.
- period-inspired denial vocabulary: switch wrong, switch unlocked, facing-point lock not engaged, detector bar occupied, protected circuit occupied, conflicting route locked, signal at danger.

## Non-Goals

- Do not start with a full dispatcher panel.
- Do not start with timetable logic.
- Do not start with a large territory.
- Do not start with realistic signal aspect systems.
- Do not start with train physics.
- Do not start with CTC, traffic control, or multiple towers.
- Do not build a generic graph safety framework before one junction works.

The first version is one visible interlocking, not a railroad operating system.

## V1 Thesis

One junction, four switches, six signals, and two trains should be enough to make route authority interesting.

The system is successful if the player can inspect a denied movement and understand the exact reason:

- occupied track circuit,
- switch not detected in the required position,
- facing-point lock not engaged,
- detector bar or protected section occupied,
- conflicting route already established,
- approach locking active,
- route not released yet.

## Model Objects

- `TrackCircuit`: an occupancy section.
- `Switch`: a movable point with commanded and detected position.
- `Lock`: a constraint that prevents switch movement or route conflict.
- `Signal`: an authority display tied to route state.
- `Route`: an origin signal, path, required switch states, protected circuits, and conflicts.
- `Train`: a simple moving occupancy source.
- `Lever` or `Control`: player command for switches, route requests, and signals.
- `Interlocking`: the rule table that validates route requests.
- `Denial`: a structured explanation for why a command failed.
- `Lever`: optional period-facing control representation tying switches, locks, signals, and routes together.

## First Questions

- Can the model prove a requested route is safe?
- Can it refuse unsafe routes for understandable reasons?
- Can track occupancy release a route deterministically?
- Can the player understand the current plant state at a glance?
- Can every signal-clearing decision be tested as data?
- Can route logic be expressed without burying the proof in UI code?

## First Runnable Moment

The first delightful runnable moment is clearing one train through one junction and then seeing a conflicting route denied with a precise reason:

```text
Requested route:
  Signal A -> Track 2

Denied:
  Switch 3 is detected NORMAL but route requires REVERSED.
  Conflicting route B -> Main is already locked.

Available action:
  Wait for route B -> Main to release, then reverse Switch 3.
```

The player should be able to ask "why not?" and get an answer from the model.

## Book-Derived Denial Taxonomy

The denial model should use railroad-specific causes when they clarify the proof:

- `switch_position_mismatch`
- `switch_not_locked`
- `facing_point_lock_not_engaged`
- `detector_bar_occupied`
- `protected_circuit_occupied`
- `conflicting_route_locked`
- `approach_locking_active`
- `route_not_released`
- `signal_held_at_danger`

Example:

```text
Requested route:
  Home Signal 2 -> East Main

Denied:
  Facing-point lock 3 is NORMAL.
  Route requires lock 3 REVERSED before Signal 2 can clear.
```

Unknown or indeterminate state should deny authority. The model should fail toward signals at danger.

## Representation Principle

The interlocking should be represented as rules over named objects, not as click handling over a drawn panel.

The source of truth should define:

- circuits,
- switches,
- signals,
- routes,
- required switch states,
- conflict sets,
- locking rules,
- release conditions.

From that source, the project should derive:

- validation,
- route requests,
- signal state,
- denial explanations,
- tests,
- diagrams or panel rendering later.

## Testing Principle

Tower's tests should read like route proof cases:

- route clears when all required conditions are true,
- route denies when a circuit is occupied,
- route denies when a switch is wrong,
- route denies when a conflicting route is locked,
- approach locking prevents unsafe cancellation,
- route releases after the train clears the protected circuits,
- signal state follows route state,
- every denial has a structured reason.

The test suite should be able to exhaustively cover a tiny plant. If the plant is too large to reason about in tests, v1 is already too large.

## V1 Scope

V1 includes:

- one fixed junction,
- four switches,
- six signals,
- named track circuits,
- two scripted or simple moving trains,
- route request controls,
- switch controls,
- signal state,
- route locking,
- conflict detection,
- occupancy detection,
- route release,
- denial explanations,
- minimal panel rendering or text UI.

V1 excludes:

- CTC,
- timetable operation,
- many trains,
- multiple towers,
- full signal aspect realism,
- train handling,
- economy,
- car movement,
- route optimization,
- large maps.

## Growth Path

### Layer 1: Route Proof

Build one interlocking where route requests clear or deny through named constraints.

### Layer 2: Approach And Release

Add approach locking, cancellation rules, and route release timing.

### Layer 3: Larger Plants

Add larger mechanical or electric interlocking plants once one junction is explainable and test-covered.

### Layer 4: CTC

Move from one local tower to remote traffic control only after the interlocking model is stable.

### Layer 5: Multi-Tower Territory

Add neighboring territories, handoff, train sheets, and larger operating pressure.

## Fit Analysis

### Fit Score

Tower is an excellent conceptual fit and a medium execution fit. It is highly aligned with proof, causality, and invalid-state prevention, but it needs a clear UI or panel representation earlier than Paper Railroad.

| Goal | Fit | Notes |
| --- | --- | --- |
| Small deterministic world | Strong | One fixed junction is compact and fully testable. |
| One fundamental object | Strong | `Route` is a natural proof object. |
| Causality and explanation | Very strong | The whole game is explaining why authority can or cannot be granted. |
| Tests as proof | Very strong | Route tables and denial cases are ideal for exhaustive tests. |
| Start delightfully small | Medium | A text/panel interface is needed for the first satisfying interaction. |
| Avoid generic-engine trap | Strong if scoped | The trap is a generic graph/interlocking framework before one plant works. |
| Personal hook | Medium to strong | It has strong railroad-system appeal, less childhood-paper-map pull than Paper Railroad. |
| Execution risk | Medium | Rule modeling is manageable; UI clarity and signal semantics can expand. |

### Why It Might Be Worth Building

Tower may be the purest "proof as gameplay" idea. It turns the question "why won't this signal clear?" into the central loop, which matches the preference for causality, diagnostics, and testable models.

It also has strong educational value: a small, inspectable interlocking could teach why safety systems are structured as constraints rather than advice.

### Main Risks

- It could become a signal-engine encyclopedia.
- UI clarity could dominate before the route model is satisfying.
- Real-world signaling vocabulary could add accidental complexity.
- Large territories could enter too early and hide the proof.
- Timetables and dispatching could pull the project away from interlocking safety.

### Scope Guardrails

- V1 must use one fixed plant.
- V1 must explain every denial.
- V1 must not model full signal aspect systems.
- V1 must not include timetable dispatching.
- V1 must derive UI state from the route model, not the reverse.

### Recommended Execution Plan

1. Define a tiny interlocking in data: circuits, switches, signals, routes, conflicts.
2. Build a route validator that returns structured approval or denial.
3. Add exhaustive tests for route requests and conflict cases.
4. Add occupancy and route release.
5. Add a minimal text or panel UI showing object states.
6. Add one simple moving-train model only as an occupancy source.
7. Write a v1 postmortem before adding CTC, larger plants, or timetable pressure.

# Cross-Reference To Railroad Designs

This document maps *The American Railway* themes to the current railroad-world designs.

Related design files:

- `../future-project-designs/railroad-worlds.md`
- `../future-project-designs/paper-railroad.md`
- `../future-project-designs/janney.md`
- `../future-project-designs/tower.md`
- `../../future-project-designs/train-book-alignment.md`
- `project-design-support.md`

## Overview

| Book Lens | Paper Railroad | Janney | Tower |
| --- | --- | --- | --- |
| Civil engineering | Route burden and capacity | Track geometry as switching constraint | Plant layout and protected paths |
| Locomotive and car mechanics | Locomotive/car classes later | Core project center | Train as occupancy source only |
| Way-bills and management | Core project center | Later car-card/scenario input | Dispatching context later |
| Freight-car service | Car availability and empty movement later | Named cars and switching puzzles | Yard/interlocking context later |
| Safety and authority | Route capacity and operating limits later | Brakes, speed, coupling safety | Core project center |
| Labor and roles | Agent, car accountant, clerk, manager | engineer, brakeman, switchman | signalman, dispatcher |
| Statistics and reports | Core output style | Replay/movement log | Route-proof/denial log |

## Paper Railroad

Current design center:

- Fundamental object: `Waybill`
- Core question: how does a transportation network create and sustain an economy?
- First runnable moment: static map analyzer

Strong book matches:

- way-bills as causal records,
- freight traffic and rates,
- car distribution,
- statistics,
- route load,
- going-concern economics,
- reports as operational truth.

Book details to import first:

1. **Civil route burden**

   A route should not be only `from`, `to`, and `distance`.

   Add design vocabulary for:

   - ruling grade,
   - curvature class,
   - bridge/tunnel burden,
   - maintenance class,
   - capacity,
   - capital burden.

2. **Way-bill accounting**

   A waybill should eventually support:

   - origin,
   - consignee/destination,
   - good,
   - quantity,
   - route,
   - revenue,
   - responsibility,
   - statistics.

3. **Report-first output**

   The first CLI should read like a small railroad office report:

   - generated way-bills,
   - unreachable demand,
   - route load,
   - bottlenecks,
   - slack,
   - going-concern note.

Recommended design edit:

Add a section to `paper-railroad.md` called `Book Lens: Civil Route Burden And Way-Bills`.

## Janney

Current design center:

- Fundamental object: `Coupler`
- Core question: how does switching actually feel?
- First runnable moment: one inglenook switching puzzle

Strong book matches:

- car identity,
- couplers,
- brakes,
- wheels,
- locomotive power,
- train as a separable chain of cars,
- switching,
- making up trains,
- mechanical explanations.

Book details to import first:

1. **Coupling event diagnostics**

   A coupling should produce a structured result:

   - cars involved,
   - coupler state,
   - impact speed,
   - alignment,
   - whether coupling succeeded,
   - why it failed if denied.

2. **Brake mode as a simplified period rule**

   Early Janney does not need full air-brake simulation, but it can distinguish:

   - locomotive brake,
   - hand brake,
   - train brake later,
   - brake delay or limited braking effect as a future option.

3. **Named cars as railroad objects**

   Cars should have identity and class:

   - boxcar,
   - hopper,
   - flat,
   - tank,
   - caboose later if useful.

Recommended design edit:

Add a section to `janney.md` called `Book Lens: Couplers, Brakes, And Car Identity`.

## Tower

Current design center:

- Fundamental object: `Route`
- Core question: how do interlockings make railroads safe?
- First runnable moment: one junction with every route clear/denial explained

Strong book matches:

- signals,
- switches,
- interlocking,
- facing-point locks,
- detector bars,
- derailing switches,
- block systems,
- home and distant signal logic,
- signalman/tower viewpoint.

Book details to import first:

1. **Route denial taxonomy**

   Denials should use railroad-specific reasons:

   - switch not in required position,
   - switch not locked,
   - detector bar occupied,
   - protected circuit occupied,
   - conflicting route locked,
   - derailer protecting movement,
   - signal cannot clear because an earlier lever/state is wrong.

2. **Fail-safe default**

   Normal/resting state should bias toward:

   - signals at danger,
   - routes uncleared,
   - protected switches locked or requiring proof,
   - unknown state treated as denial.

3. **Lever/table representation**

   Even if the UI is not a full mechanical frame, the model can feel period-correct by representing route logic as named levers, switches, locks, and signals.

Recommended design edit:

Add a section to `tower.md` called `Book Lens: Interlocking As Route Proof`.

## Shared Vocabulary

See `project-design-support.md` for a more detailed vocabulary table with project meanings.

Prefer these terms where they clarify the model:

- way-bill,
- route,
- ruling grade,
- road-bed,
- bridge rating,
- track circuit,
- home signal,
- distant signal,
- facing-point lock,
- detector bar,
- derailing switch,
- block,
- car accountant,
- train despatcher,
- station agent,
- section boss,
- switchman,
- engineer,
- fireman,
- brakeman,
- consist,
- slack,
- coupler,
- air-brake,
- hand-brake.

Avoid using period vocabulary when it hides the model. The word should earn its place by mapping to a rule, diagnostic, state field, report, or test.

## Shared Output Style

The book suggests that outputs should feel like railroad records.

Paper Railroad:

```text
Way-bill and route-load report.
```

Janney:

```text
Movement and coupling log.
```

Tower:

```text
Route proof and denial report.
```

This is a practical way to preserve the book's spirit without starting with historical UI.

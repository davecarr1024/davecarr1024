# Janney Design Doc

## Core Question

How does switching actually feel when the coupler is treated as the center of the railroad world?

Janney is not a railroad tycoon game, not a dispatching game, and not a route-planning game. It is a small physical toy about making and breaking trains. The interesting part is local and tactile: slack runs in and out, cars bump together, couplers lock or fail to lock, a cut rolls too far or not far enough, and a switching move succeeds because the player understood the train as a chain of masses rather than a single object.

## Fantasy

I am standing beside the train.

I do not care about scenery yet. I do not care about industries yet. I care about the physical act of switching:

- coupling,
- uncoupling,
- pulling,
- shoving,
- stopping,
- letting slack settle,
- making a cut,
- sorting cars into a small yard.

The first version should make one inglenook satisfying before it tries to become a world.

## Fundamental Object

`Coupler`.

The coupler is the reason freight railroading is mechanically interesting. Cars are not just sprites behind a locomotive. They are separable bodies that can become a train, stop being a train, transfer force through slack, and be rearranged by local decisions.

Everything in Janney should support the coupler:

- car spacing,
- slack state,
- coupling threshold,
- uncoupling command,
- compressive and tensile force,
- impact speed,
- train segmentation,
- puzzle state.

## Non-Goals

- Do not start with an economy.
- Do not start with industries.
- Do not start with waybills.
- Do not start with dispatching or signals.
- Do not start with a full layout editor.
- Do not start with procedural scenery.
- Do not start with realistic 3D graphics.
- Do not model every air-brake, knuckle, hose, draft gear, and handbrake detail in v1.

The first version is not a complete train simulator. It is a tiny switching feel laboratory.

## V1 Thesis

One locomotive, eight cars, three sidings, and one inglenook should be enough to answer whether the project has a soul.

If pushing cars around is not fun in that setup, adding scenery, industries, maps, or progression will not save it.

## Model Objects

- `Track`: a one-dimensional path with switch-connected branches.
- `Switch`: a track decision point with normal and reversed routes.
- `Car`: a body with length, mass, position, velocity, and coupler endpoints.
- `Locomotive`: a car-like body with traction and braking input.
- `Coupler`: an endpoint that may be open, closed, coupled, or blocked.
- `Consist`: a connected set of cars whose forces propagate through couplers.
- `Slack`: compression or stretch between coupled cars.
- `Move`: a player-intended action such as pull, shove, stop, uncouple, or throw switch.
- `Puzzle`: an initial arrangement, target arrangement, and scoring rules.

## First Questions

- Can the player reliably couple two cars without the interaction feeling arbitrary?
- Can slack be felt and used without becoming frustrating?
- Can cars be sorted through an inglenook with a small rule set?
- Can the simulation explain why a coupling failed?
- Can the puzzle state be validated from the model rather than from screen state?
- Can the system replay the same inputs deterministically?

## First Runnable Moment

The first delightful runnable moment is one switching puzzle:

```text
Goal:
  Build train: Loco - Boxcar 3 - Tank 1 - Hopper 2

Current:
  Main: Loco, Boxcar 1, Hopper 2
  Siding A: Tank 1, Boxcar 3
  Siding B: Hopper 4

Last event:
  Coupled Boxcar 3 to Tank 1 at 1.2 mph.
  Coupler closed: yes.
  Slack state: compressed.
```

The screen can be plain. The important thing is that coupling, uncoupling, pushing, and stopping feel legible.

## Representation Principle

The physical model should be one-dimensional first.

The representation should understand track topology and distance along a path. Rendering can project that world into 2D later. If v1 starts with screen coordinates as the source of truth, the physics and switching logic will become harder to test.

The core model should support:

- deterministic stepping,
- fixed timestep,
- replayable input events,
- structured event output,
- inspectable car positions and coupler states,
- test fixtures that do not need a renderer.

## Testing Principle

Janney's tests should prove physical and puzzle invariants:

- cars do not pass through each other,
- coupled cars remain connected unless uncoupled or broken by an explicit rule,
- open couplers do not couple,
- closed compatible couplers couple within threshold,
- impact speed affects coupling outcome if modeled,
- switch state controls traversal,
- puzzle completion derives from car identity and order,
- replayed inputs produce the same final state.

Visual tests can help later, but the core proof should be model-level.

## V1 Scope

V1 includes:

- one fixed inglenook layout,
- one locomotive,
- eight cars,
- three sidings,
- keyboard controls,
- fixed timestep simulation,
- coupling and uncoupling,
- switch throwing,
- puzzle target order,
- deterministic replay or logged input trace,
- text or minimal 2D rendering.

V1 excludes:

- save/load,
- layout editor,
- generated puzzles,
- economy,
- industries,
- signals,
- AI crews,
- multiplayer,
- complex scenery,
- full railroad rulebook.

## Growth Path

### Layer 1: Switching Feel

The project starts with only the physical act of switching. Get coupling, slack, and stopping right enough to make one puzzle satisfying.

### Layer 2: Scenario System

Add multiple switching puzzles, target manifests, scoring, and replay review.

### Layer 3: Layout Editor

Add a small spline or graph-based editor only after the fixed inglenook has proven the model.

### Layer 4: Operational Context

Add industries, car cards, waybills, and simple reasons for cars to move.

### Layer 5: World Layer

Only after the switching toy works should scenery, tile-world influence, or AI crews enter.

## Fit Analysis

### Fit Score

Janney is a strong fit for the design goals, but it has higher execution risk than Paper Railroad because physical feel is hard to specify and tune.

| Goal | Fit | Notes |
| --- | --- | --- |
| Small deterministic world | Strong | One inglenook can be tiny and replayable. |
| One fundamental object | Strong | `Coupler` is concrete, railroad-specific, and organizing. |
| Causality and explanation | Medium to strong | Coupling failures and slack events can explain themselves, but feel still matters. |
| Tests as proof | Medium | Physics invariants test well; "fun switching feel" needs manual judgment. |
| Start delightfully small | Medium | The first runnable moment needs interaction and tuning, not just correctness. |
| Avoid generic-engine trap | Medium | Spline editor, physics engine, and layout framework are tempting traps. |
| Personal hook | Strong | It connects Tracky-style operations with a very tactile railroad mechanic. |
| Execution risk | Medium to high | Coupling, slack, collision, and controls can become fiddly. |

### Why It Might Be Worth Building

Janney has the strongest "playable toy" potential. If it works, it could become the most immediately delightful of the railroad ideas because the player can feel the system through direct manipulation.

It also complements Paper Railroad well. Paper Railroad explains why cars should move. Janney explains how local work turns cars into trains.

### Main Risks

- Physics tuning could swallow the project.
- Rendering and input could become more urgent than the model.
- A layout editor could appear before the fixed puzzle is satisfying.
- Realism could creep in through brakes, draft gear, coupler mechanics, and yard rules.
- Tests can prove invariants but cannot fully prove game feel.

### Scope Guardrails

- V1 must use one fixed layout.
- V1 must not include an economy.
- V1 must not include a layout editor.
- V1 must keep physics one-dimensional.
- V1 should explain events in text or structured logs even if the visual layer is simple.

### Recommended Execution Plan

1. Build a headless model for track positions, cars, couplers, and fixed timestep updates.
2. Add tests for coupling thresholds, uncoupling, collision prevention, and switch traversal.
3. Add a minimal renderer only after the model can run a scripted move.
4. Add keyboard controls and one fixed inglenook.
5. Add puzzle target validation and completion explanation.
6. Tune only the small set of values that affect coupling, slack, traction, and braking.
7. Write a v1 postmortem before adding editor or economy layers.

Railroad Worlds

A Family of Executable Models

Rather than one giant railroad simulator, I want to build a family of small projects. Each one isolates a different aspect of railroading and asks:

«What is the smallest executable model that captures why this part of railroading is interesting?»

Each project should stand on its own. They should share philosophy, not necessarily code.

---

Project 1: Paper Railroad

Core Question

How does a transportation network create and sustain an economy?

The Fantasy

I am the owner of a small railroad.

I don't drive trains.

I create a transportation network that allows goods to move between industries.

Fundamental Object

Waybill

Nothing moves without a waybill.

Waybills are the causal object from which everything else is derived.

They represent:

- demand
- shipment
- routing
- revenue
- resource consumption

The railroad exists to execute waybills.

Initial Scope

Static.

No clock.

No trains.

No dispatcher.

Represent:

- towns
- industries
- routes
- distances
- producers
- consumers
- goods
- waybills

Answer questions like:

- Is every demand reachable?
- Is supply balanced?
- Which routes are bottlenecks?
- What transport capacity is required?
- Can the railroad become a going concern?

Growth Path

Version 2

- operating costs
- rates
- profitability
- empty-car movements

Version 3

- discrete time
- shipments in transit

Version 4

- actual trains executing waybills

---

Project 2: Janney

Core Question

How does switching actually feel?

The Fantasy

I am standing beside the train.

I don't care about scenery.

I care about making and breaking trains.

Fundamental Object

Coupler

The coupler is the heart of freight railroading.

Everything interesting happens because cars can be assembled into trains, separated, and reassembled somewhere else.

Differentiator

Not another railroad tycoon.

Not dispatching.

Not route planning.

A toy centered on realistic one-dimensional railroad physics.

The interesting mechanics are:

- slack
- momentum
- coupling
- uncoupling
- rolling cuts
- switching puzzles

Initial Scope

One inglenook.

One locomotive.

Eight cars.

Three sidings.

Simple spline track.

No scenery.

No industries.

No economy.

No AI.

If pushing cars around is not fun, stop.

Growth Path

Version 2

- spline layout editor
- save/load

Version 3

- switching scenarios
- scoring

Version 4

- procedural scenery

Version 5

- industries
- waybills
- AI crews

---

Project 3: Tower

Core Question

How do interlockings make railroads safe?

The Fantasy

I am standing in the control tower overlooking an interlocking.

I do not drive trains.

I do not tell engineers how to operate.

I establish the constraints under which trains are allowed to move.

My job is to ensure dangerous situations cannot emerge.

Fundamental Object

Route

The route is the proof.

Every cleared signal represents a demonstrated safe path through the railroad.

Core Mechanics

Player actions:

- throw switches
- request routes
- clear signals

System responsibilities:

- lock points
- detect occupancy
- enforce conflicting routes
- maintain approach locking
- release routes

Interesting Gameplay

The puzzle is not:

«How fast can I click?»

The puzzle is:

«Why won't this signal clear?»

Possible reasons:

- occupied track circuit
- detector bar occupied
- switch not detected
- facing-point lock not engaged
- conflicting route established
- derailer protecting siding
- approach locking active

Every denied movement should have an explanation.

Initial Scope

One junction.

Four switches.

Six signals.

Two trains.

Everything visible.

Every decision explainable.

Growth Path

Version 2

- larger plants
- mechanical interlocking

Version 3

- electric interlocking

Version 4

- CTC

Version 5

- multiple towers

---

Shared Design Principles

Small Worlds

Every project should be tiny.

The first version should be completable in weeks, not years.

One Fundamental Object

Every project revolves around a single idea.

Paper Railroad

Waybill.

Janney

Coupler.

Tower

Route.

Everything else exists to support that object.

Causality

Every interesting event should answer:

Why?

The debugger is part of the game.

Players should be able to inspect:

- why a shipment exists
- why cars coupled
- why a signal cleared
- why a route failed
- why a bottleneck formed

Deterministic

The worlds should be replayable.

The same inputs should always produce the same outputs.

Representation First

Spend more time finding the right model than the right algorithm.

Once the representation is correct, the implementation should become straightforward.

Build Delight First

Every project should have a runnable moment almost immediately.

Paper Railroad

A map analyzer that explains an economy.

Janney

Successfully completing one switching puzzle.

Tower

Safely routing one train through an interlocking.

That first delightful moment is not the end of the project.

It is the reason the rest of the project gets built.

---

Relationship Between Projects

These are not different games.

They are different perspectives on the same world.

Paper Railroad

"What should move?"

Models information.

Flows.

Economics.

Demand.

Janney

"How does it move?"

Models physical motion.

Momentum.

Couplers.

Switching.

Tower

"When may it move?"

Models authority.

Signals.

Interlocking.

Safety.

Together they describe a railroad from three independent viewpoints.

Each is intentionally small.

Each explores one beautiful abstraction.

Each tries to make an invisible system visible.

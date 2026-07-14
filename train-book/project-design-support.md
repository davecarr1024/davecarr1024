# Project Design Support

This document turns the train-book analysis into concrete support for the railroad project designs.

Use this when editing:

- `../future-project-designs/railroad-worlds.md`
- `../future-project-designs/paper-railroad.md`
- `../future-project-designs/janney.md`
- `../future-project-designs/tower.md`
- `../future-project-designs/railroad-fit-analysis.md`
- `../future-project-designs/train-book-alignment.md`

## Design Rule

Use *The American Railway* as a source of executable texture.

A book detail is worth importing when it becomes one of:

- a model field,
- a validation rule,
- a diagnostic reason,
- a report section,
- a test fixture,
- a project vocabulary choice,
- a future phase boundary.

A book detail is not worth importing when it only becomes decoration, historical flavor text, or a large fidelity burden before the small world works.

## Shared Project Vocabulary

These terms are good candidates because they map cleanly to project model state.

### Freight And Records

| Term | Project Meaning |
| --- | --- |
| way-bill | Causal record authorizing and explaining a shipment |
| consignee | Destination or receiver for a shipment |
| route | Chosen path or proven authority, depending on project |
| car accountant | Role implied by reports about car location and responsibility |
| tracer | Later tool/report for finding delayed or missing cars |
| empty car | Later capacity object needed before a shipment can move |
| rate | Revenue rule for moving freight |
| division | Later operating subdivision or accounting boundary |

### Civil Engineering

| Term | Project Meaning |
| --- | --- |
| ruling grade | Route constraint that limits train size or capacity |
| curvature class | Route constraint that limits speed or equipment |
| road-bed | Route infrastructure baseline |
| bridge rating | Load or capacity constraint |
| tunnel burden | Capital/maintenance burden and possible clearance constraint |
| trestle | Temporary or cheaper structure with maintenance/safety implications |
| section boss | Role implied by maintenance diagnostics |

### Mechanical

| Term | Project Meaning |
| --- | --- |
| coupler | Central endpoint for joining cars |
| slack | Compression/stretch state in a consist |
| air-brake | Later train-wide braking rule |
| hand-brake | Local car brake rule or simplified holding state |
| adhesion | Locomotive force limit before wheel slip |
| driver | Wheel set receiving locomotive power |
| injector | Later locomotive subsystem if steam operation becomes active |
| throttle | Locomotive control input |

### Safety And Authority

| Term | Project Meaning |
| --- | --- |
| home signal | Signal governing entry into protected limits |
| distant signal | Advance warning/caution signal |
| block | Occupancy interval between trains |
| interlocking | Rule system preventing incompatible switch/signal states |
| facing-point lock | Required proof that a switch is locked for a facing move |
| detector bar | Occupancy protection that prevents unsafe switch movement |
| derailing switch | Protective device that intentionally prevents an unsafe entry |
| signal at danger | Fail-safe authority denial |

## Paper Railroad Support

### Book Basis

Paper Railroad should draw most directly from:

- `Railway Management`
- `The Freight-Car Service`
- `The Railway in Its Business Relations`
- `Statistical Railway Studies`
- `The Building of a Railway`

The book sees freight through records and statistics. That supports making `Waybill` the central object.

### Design Imports

V1-safe imports:

- way-bill as the causal demand object,
- route-load report,
- unreachable demand report,
- bottleneck report,
- route capacity,
- role-labeled diagnostics from the station agent or traffic office viewpoint.

V1.5 or v2 imports:

- route burden from grade, curve, bridge, or tunnel,
- revenue/rate fields,
- operating-cost fields,
- empty-car demand,
- car-accounting reports,
- route investment choices.

Avoid in v1:

- full tariff law,
- real railroad interchange rules,
- detailed car-hire accounting,
- moving trains,
- dispatching,
- crew management.

### Suggested Diagnostics

```text
Traffic Office:
  6 way-bills generated.
  5 can be routed.
  1 cannot be routed because Foundry has no reachable coal supply.
```

```text
Engineering Office:
  Foundry Branch is saturated.
  Cause: 4 coal/day demanded, 3 coal/day route capacity.
  Future explanation may include ruling grade or bridge rating.
```

```text
Car Accountant:
  Empty-car movement is not modeled in this version.
  Treating all way-bills as unconstrained by car supply.
```

### Tests The Book Lens Suggests

- A waybill exists for every served demand.
- An unreachable demand names the missing route or missing supply.
- A bottleneck names the contributing waybills.
- A route with insufficient capacity rejects or flags excess traffic.
- Later: a route with a severe grade reduces effective capacity.

## Janney Support

### Book Basis

Janney should draw most directly from:

- `American Locomotives and Cars`
- `Safety in Railroad Travel`
- `The Freight-Car Service`
- `The Every-Day Life of Railroad Men`

The book sees cars as physical and operational objects. That supports making `Coupler` the central object and making cars named, inspectable bodies.

### Design Imports

V1-safe imports:

- named cars,
- coupler state,
- impact speed,
- slack state,
- brake/held state in simplified form,
- movement log,
- switch traversal reasons.

V1.5 or v2 imports:

- hand brake vs train brake distinction,
- car class and weight,
- locomotive adhesion limit,
- grade resistance,
- brake delay or propagation,
- car cards or waybill-derived switching scenarios.

Avoid in v1:

- full steam locomotive simulation,
- full air-brake plumbing,
- full draft-gear mechanics,
- realistic damage,
- layout editor,
- large yard operations.

### Suggested Diagnostics

```text
Switchman:
  Coupling attempt failed.
  Boxcar 3 coupler is closed, Tank 1 coupler is closed.
  Open one coupler before impact.
```

```text
Brakeman:
  Cut moved 2.4 car-lengths after uncoupling.
  Hand brake was not set.
```

```text
Engineer:
  Locomotive slipped.
  Requested shove exceeds available adhesion for this consist.
```

### Tests The Book Lens Suggests

- Closed couplers do not couple if the rule requires one open knuckle.
- Coupling success records impact speed and resulting slack state.
- Cars remain named and ordered after switching moves.
- A brake or holding state prevents a car from rolling when expected.
- Later: excessive force or grade causes slip rather than impossible acceleration.

## Tower Support

### Book Basis

Tower should draw most directly from:

- `Safety in Railroad Travel`
- `Railway Management`

The book sees safety as an interaction between discipline, signals, brakes, switches, blocks, and interlocking. That supports making `Route` the proof object.

### Design Imports

V1-safe imports:

- signal defaults to danger,
- route request proof,
- switch position and detection,
- lock state,
- conflicting routes,
- occupied protected circuits,
- structured denial reasons.

V1.5 or v2 imports:

- facing-point locks,
- detector bars,
- derailing switches,
- distant vs home signals,
- approach locking,
- block intervals,
- train-order or telegraph context.

Avoid in v1:

- full signal aspect encyclopedia,
- full timetable dispatching,
- many towers,
- broad CTC territory,
- realistic train handling.

### Suggested Diagnostics

```text
Signalman:
  Signal 2 cannot clear.
  Switch 4 is NORMAL.
  Route requires Switch 4 REVERSED and locked.
```

```text
Interlocking:
  Route A -> Main denied.
  Conflicting route B -> Main is already locked.
```

```text
Block Report:
  East Main occupied.
  Signal remains at danger until the protected circuit clears.
```

### Tests The Book Lens Suggests

- Signals start at danger.
- A route clears only when all switch, lock, occupancy, and conflict requirements are met.
- A route denial names the first or all failed proof conditions.
- Occupancy prevents protected route clearance.
- A conflicting locked route prevents another route from clearing.
- Unknown detection state denies authority.

## Shared Report Style

The book's period texture is strongest when outputs resemble operational records.

Prefer:

- concise reports,
- tables,
- named roles,
- structured causes,
- movement logs,
- route proofs,
- way-bill summaries.

Avoid:

- long in-app historical exposition,
- decorative old-paper styling before model behavior exists,
- generic "error" messages when a railroad-specific cause is available.

## Shared Phase Boundary

Each project should add train-book detail in this order:

1. Vocabulary: name the object in railroad terms.
2. State: represent the term as model data.
3. Rule: make the state affect behavior.
4. Diagnostic: explain the effect in railroad language.
5. Test: prove the behavior and explanation.

Do not skip from vocabulary directly to broad simulation.

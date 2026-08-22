# Train Book Alignment

This document analyzes how the railroad-world project ideas can preserve the spirit, period, and technical texture of *The American Railway: Its Construction, Development, Management, and Appliances*.

The goal is not to turn the book into requirements. The goal is to make the book's worldview explicit enough that future railroad projects can inherit it deliberately.

Source used for this pass:

- Public-domain Internet Archive scan: `americanrailwayi00coolrich`
- Original edition: Charles Scribner's Sons, 1889
- Main title: *The American Railway: Its Construction, Development, Management, and Appliances*

## Core Thesis

The book treats the railroad as one interconnected industrial organism:

- civil engineering makes the physical way possible,
- locomotive and car engineering turn steam, weight, adhesion, wheels, brakes, and couplers into motion,
- management turns movement into schedules, accounting, way-bills, car distribution, and revenue,
- safety systems turn dangerous motion into constrained motion,
- labor turns rules and machinery into daily operation.

The railroad-world projects should keep that organism visible, but each project should isolate one organ at a time.

Paper Railroad should inherit the book's paperwork, traffic, freight, and management logic.

Janney should inherit the book's mechanical-car and train-handling logic.

Tower should inherit the book's safety, signal, switch, and interlocking logic.

The projects should share period vocabulary and causal explanations, not necessarily code.

## Book-Derived Lenses

### 1. Civil Engineering Lens

Most relevant book sections:

- `The Building of a Railway`
- `Feats of Railway Engineering`

Important concepts:

- survey before construction,
- locating a line through real terrain,
- grades and curves as economic and mechanical compromises,
- road-bed, cuts, fills, embankments, culverts, bridges, tunnels, and trestles,
- sharp curves and switchbacks as practical alternatives to expensive tunnels,
- bridge material and construction limits,
- track laying and maintenance,
- section bosses and distributed maintenance responsibility.

Project implications:

- Routes should not be abstract edges forever. Even in a static model, a route can carry engineering facts: distance, ruling grade, curvature, bridge/tunnel burden, maintenance cost, and capacity.
- A route should explain why it is expensive or limiting. For example: grade limits train size, curvature limits speed, bridge rating limits axle load, or a tunnel/trestle raises capital cost.
- Civil constraints should appear before full train simulation. Paper Railroad can use them as static route attributes.

Good first import:

```text
Route {
  distance
  ruling_grade
  curvature_class
  structure_burden
  maintenance_class
  capacity
}
```

The output should explain bottlenecks in railroad language:

```text
Foundry Branch is capacity-limited by ruling grade, not by distance.
The route can carry the demanded coal flow only if train size is reduced or service frequency increases.
```

### 2. Locomotive And Car Lens

Most relevant book section:

- `American Locomotives and Cars`

Important concepts:

- steam generation,
- boiler, firebox, injector, throttle, cylinders, slide valves, valve gear, rods, drivers, trucks, frames, and tender,
- adhesion as the limit between power and slipping wheels,
- wheel arrangement as a compromise between tractive effort, speed, rail load, and curve negotiation,
- car evolution from wagon-like bodies to trucked cars,
- car wheels, frames, couplers, and freight/passenger car types,
- fuel and water as operating constraints,
- shop work and locomotive care.

Project implications:

- Janney should treat a train as a chain of separate bodies, not as a single moving token.
- Locomotive power should eventually be constrained by adhesion and train resistance, not arbitrary acceleration.
- Paper Railroad can use locomotive classes abstractly before physics exists: a route may require a locomotive type because of grade, rail load, or train size.
- The "mechanical explanation" style matters. When something fails, the project should say whether it failed because of adhesion, excessive speed, car length, coupler state, brake state, or route geometry.

Good first import for Janney:

```text
CouplerEvent {
  leading_car
  trailing_car
  impact_speed
  coupler_states
  result
  explanation
}
```

Good later import:

```text
LocomotiveClass {
  adhesive_weight
  driver_diameter
  boiler_capacity_class
  tractive_effort_class
  allowed_route_classes
}
```

### 3. Way-Bill And Management Lens

Most relevant book sections:

- `Railway Management`
- `The Freight-Car Service`
- `Statistical Railway Studies`

Important concepts:

- time-tables,
- train dispatching by diagram and telegraph,
- car distribution,
- foreign cars and car accounting,
- lost cars and tracers,
- freight houses and yards,
- train make-up,
- way-bills as the core paper object for freight movement, revenue, accountability, and statistics,
- rates, divisions, revenue, disbursements, and reports.

Project implications:

- Paper Railroad's `Waybill` is exactly the right fundamental object.
- A waybill should not be only "demand." It should become a causal record that ties together origin, destination, good, quantity, route, carrier responsibility, revenue, and later car movement.
- The analyzer should produce statistics because the book's management chapters see the railroad through records.
- "Going concern" should be framed in period terms: traffic, revenue, route burden, car use, empty movement, and operating expense.

Good first import:

```text
Waybill {
  origin
  destination
  good
  quantity
  route
  revenue
  required_capacity
  explanation
}
```

Good report style:

```text
Way-bill summary:
  4 coal way-bills generated.
  3 can reach their consignees.
  1 fails because no route connects Mine to Foundry with sufficient bridge rating.
```

### 4. Safety And Authority Lens

Most relevant book sections:

- `Safety in Railroad Travel`
- `Railway Management`

Important concepts:

- hand brakes and air brakes,
- continuous braking as a system-level safety appliance,
- signals that protect danger points,
- signals that maintain interval between trains,
- semaphore signals,
- block signaling,
- interlocked switches and signals,
- facing-point locks,
- detector bars,
- derailing switches,
- tower-controlled routes,
- discipline, rules, and dispatching precautions.

Project implications:

- Tower's `Route` is the right fundamental object because the book presents safety as constrained permission.
- A cleared route should mean a proof has succeeded, not that a UI button changed color.
- Denials should use book-period terms where possible: switch not locked, point not detected, conflicting route, occupied circuit, signal at danger, block occupied, approach not clear.
- Safety appliances should have fail-safe bias: loss of a required condition should deny authority.

Good first import:

```text
RouteDenial {
  route
  reason_kind
  affected_object
  required_state
  actual_state
  explanation
}
```

The core Tower loop should be:

```text
request route -> prove switch/lock/occupancy/conflict conditions -> clear or deny with reasons
```

### 5. Labor And Daily Operation Lens

Most relevant book sections:

- `The Every-Day Life of Railroad Men`
- `The Prevention of Railway Strikes`
- `How to Feed a Railway`

Important concepts:

- engineers, firemen, brakemen, conductors, station agents, switch-tenders, section-men, dispatchers, clerks, shop workers,
- vigilance and discipline,
- maintenance, stores, purchasing, fuel, rails, ties, tools, pay cars, and supply chains,
- promotion, roles, and institutional memory.

Project implications:

- The early projects should not simulate labor in detail, but they should not erase labor either.
- Diagnostics can name the role implied by a decision: dispatcher, station agent, car accountant, section boss, signalman, engineer.
- Later versions can add role-specific viewpoints instead of generic "player actions."

Good first import:

```text
Diagnostic {
  role: "car accountant" | "dispatcher" | "signalman" | "section boss"
  finding
  evidence
}
```

## Alignment Matrix

| Project | Book Center | Strong Existing Match | Missing Book-Derived Detail | Best First Import |
| --- | --- | --- | --- | --- |
| Paper Railroad | Way-bills, freight, management, statistics, civil-route burden | `Waybill` as causal object; static map analyzer; going-concern question | Route engineering attributes; car distribution; period accounting vocabulary | Add route burden fields and way-bill summary diagnostics |
| Janney | Cars, couplers, braking, train handling, locomotive mechanics | `Coupler` as central object; one-dimensional switching; slack and momentum | Air/hand brake distinction; impact-speed explanations; car class and wheel/load constraints | Add structured coupling and braking event explanations |
| Tower | Signals, switches, interlocking, block safety, dispatching discipline | `Route` as proof; denied movement explanations; one fixed junction | Period terms: facing-point locks, detector bars, derailing switches, home/distant signals | Add route-denial taxonomy based on interlocking conditions |

## Recommended Automated Analysis

The analysis can become a repeatable local tool without needing a large AI system.

### Inputs

- OCR text of *The American Railway*
- Markdown project designs in `future-project-designs/`
- A hand-maintained topic map that names the book lenses above

### Derived Files

```text
research/train_book/derived/
  book-topics.yaml
  period-terms.yaml
  project-matches.md
  import-candidates.md
```

### Topic Map Shape

```yaml
topics:
  civil_engineering:
    sections:
      - The Building of a Railway
      - Feats of Railway Engineering
    terms:
      - grade
      - curve
      - road-bed
      - bridge
      - tunnel
      - ballast
      - track

  locomotive_mechanics:
    sections:
      - American Locomotives and Cars
    terms:
      - boiler
      - injector
      - cylinder
      - valve gear
      - driving wheels
      - adhesion
      - coupler
      - brake
```

### Report Algorithm

1. Split the book OCR into chapter-like sections using the table of contents and headings.
2. Count topic terms per section and keep nearby snippets for human review.
3. Count the same topic terms in each project design.
4. Produce a matrix showing strong, weak, and absent matches.
5. For each weak match, suggest one import candidate that is small enough for v1 or v2.
6. Keep generated reports separate from hand-written design docs until a project is active.

This preserves inspectability: every suggestion can point back to a topic, section, term cluster, and project file.

## Concrete Next Bites

### Bite 1: Add A Book Lens File

Create a small structured `book-topics.yaml` with the five topic lenses:

- civil engineering,
- locomotive and car mechanics,
- way-bill and management,
- safety and authority,
- labor and daily operation.

Done when a script or manual report can list which terms belong to which lens.

### Bite 2: Generate A First Match Report

Scan:

- `paper-railroad.md`
- `janney.md`
- `tower.md`
- `railroad-worlds.md`

Produce a generated Markdown report that says which book lenses are present in each project.

Done when the report distinguishes between exact term matches and human-curated import suggestions.

### Bite 3: Promote One Import Into Paper Railroad

Paper Railroad is still the best first project. The most useful book-derived addition is route engineering burden:

- distance,
- ruling grade,
- curvature class,
- bridge/tunnel burden,
- maintenance class,
- capacity.

Done when the Paper Railroad design says that a route is not just an edge; it is a civil-engineering compromise that affects transport capacity and cost.

## Design Guardrails

- Do not require every project to represent the whole book.
- Do not let book fidelity override small-world clarity.
- Do not start with a generic railroad ontology.
- Do not import details unless they create executable rules, diagnostics, or tests.
- Prefer period vocabulary when it clarifies the model.
- Keep the book as a lens, not a cage.

## Summary

The current railroad-world project family already matches the book better than it first appears:

- Paper Railroad inherits the management and way-bill worldview.
- Janney inherits the mechanical and car-handling worldview.
- Tower inherits the safety and interlocking worldview.

The missing piece is an explicit train-book alignment layer that keeps the 1889 engineering and operating texture available as projects evolve.

The strongest next move is to formalize the book lenses, then use them to enrich Paper Railroad's static map analyzer with civil-engineering route burden and period way-bill diagnostics.

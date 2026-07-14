# Paper Railroad Design Doc

## Train Book Lens

Paper Railroad is explicitly inspired by *The American Railway*, especially the book's management, freight, way-bill, statistical, and civil-engineering chapters.

Primary cross-references:

- `../train-book/themes.md`: themes 2, 4, 5, 7, and 9.
- `../train-book/cross-reference.md`: `Paper Railroad`.
- `../train-book/fingerprint.md`: chapter map and term counts for freight, cars, way-bills, route burden, and statistics.
- `train-book-alignment.md`: `Way-Bill And Management Lens` and `Civil Engineering Lens`.

The book-derived rule for this project is: a railroad economy should be explained through records. The first useful artifact should feel like a small railroad office report: generated way-bills, route loads, bottlenecks, unreachable demands, and later revenue or car-accounting summaries.

## Core Question

Can a tiny paper railroad economy be represented, analyzed, and eventually operated as a small deterministic world?

The seed is not "build a train simulator." The seed is the childhood paper map: towns as dots, lines as routes, marks as distance, cars as goods, and laps around the physical layout as ritualized travel. The interesting part is that the simple paper system was already an economic simulation. Towns produced things, towns wanted things, cars represented loads, routes had distance and risk, and the railroad existed to make the system balance.

The first project should preserve that clarity.

## Why This Fits

Paper Railroad combines several durable interests without starting in the most dangerous place.

- It has the load-and-balance structure of schedulability and compute-cell simulation.
- It has the operations flavor of Tracky, but at a higher and more diagrammatic level.
- It has a personal emotional hook instead of starting from an abstract systems problem.
- It can begin as a static model, like the HDL layer in IRATA2, before any clock or simulation loop exists.
- It naturally supports causality: every shipment can explain why it exists, where it can go, what capacity it consumes, and whether it was economically worthwhile.
- It has historical texture from *The American Railway*: way-bills, car movement, route burden, railroad statistics, and the question of whether a line is a going concern.

The right framing is not "toy railroad" and not "Borg but trains." It is a miniature economic railway laboratory.

## Fit Analysis

### Fit Score

Paper Railroad is the strongest fit for the stated design and execution goals.

| Goal | Fit | Notes |
| --- | --- | --- |
| Small deterministic world | Strong | V1 can be purely static: one map, one economy, one analyzer. |
| One fundamental object | Strong | `Waybill` naturally organizes demand, routing, load, revenue, and explanation. |
| Causality and explanation | Strong | Every result can answer which demands, producers, consumers, and routes caused it. |
| Tests as proof | Strong | The project can be built as a suite of map fixtures and asserted diagnostics. |
| Start delightfully small | Strong | A CLI map analyzer can be useful before any UI, clock, or train simulation exists. |
| Avoid generic-engine trap | Strong if scoped | The danger is turning "map analyzer" into a universal logistics framework. Keep v1 concrete. |
| Personal hook | Strong | It connects directly to the childhood paper railroad map. |
| Execution risk | Low to medium | The first useful version is mostly representation, validation, graph traversal, and explanation. |

### Why It Should Probably Come First

Paper Railroad has the cleanest first move. It does not require tuning game feel, rendering, input, physics, or UX before it can become satisfying. The first deliverable can be a deterministic proof:

- read a tiny map,
- validate the world,
- derive waybills,
- compute reachability and route load,
- print causal explanations,
- assert the whole thing in tests.

That matches the core developer record almost exactly. It is an executable model where the proof suite is the product.

### Main Risks

- It could become an abstract network-flow library instead of a paper railroad.
- It could over-model railroad accounting before the transport model is interesting.
- It could drift toward a simulation engine before the static analyzer has earned time.
- C++ type-system modeling could become the project rather than serving the model.

### Scope Guardrails

- V1 must not include moving trains.
- V1 must not include a UI.
- V1 must not include full tariff law, crew rules, yard operations, car hire, or interchange realism.
- V1 should have one map, one or two goods, one routing policy, and one excellent explanation.

### Recommended Execution Plan

1. Write `docs/design.md` from this design when the project repo is created.
2. Define a tiny declarative map format.
3. Build validation first: unknown towns, unknown goods, disconnected routes, invalid quantities.
4. Build waybill derivation from producers and consumers.
5. Build route selection and route-load explanation.
6. Add tests for every invalid and interesting map.
7. Only then consider capacity, slack, and going-concern accounting.

## Non-Goals

- Do not start with train physics.
- Do not start with dispatching.
- Do not start with a generic simulation engine.
- Do not start with an RPG-like world model.
- Do not model real railroad law, accounting, or operations in full fidelity.
- Do not build a UI before the model has interesting answers.

The first version should not have time, ticks, trains, crews, switches, yards, locomotives, consists, timetables, or collisions. Those may become interesting later, but they are not the foundation.

## Versioning Philosophy

Do not try to design the perfect railroad model on the first pass.

The healthy pattern is IRATA to IRATA2: build one concrete version, discover the design regrets honestly, then use those regrets as the specification for a cleaner second version. IRATA2 was fun because it did not start from a blank fantasy of perfect architecture. It started from lived experience with IRATA: what the language definition wanted to be, where the HDL needed stronger boundaries, how the control system should be represented, and which abstractions had earned their place.

Doki is the missed versioning lesson. At the point where the system had produced real insight but started losing coherence, it might have survived as knowledge rather than code: write down the lessons, throw away the unstable implementation, and rebuild a smaller v2 around the lessons that still mattered.

Paper Railroad should explicitly embrace that cycle.

### V1 Is Allowed To Be Wrong

The first version can have a bad map format, a naive routing policy, a simplistic economy, and ugly output. That is acceptable if it produces concrete examples and teaches which questions are actually interesting.

V1 should optimize for learning:

- one map,
- one or two goods,
- one routing policy,
- one printed explanation,
- one obvious bottleneck,
- one clear design regret.

The goal is not to avoid regret. The goal is to make the regrets specific enough to guide v2.

### Rebuilds Need A Reason

Versioning is not the same as rebuilding the same project forever.

A rewrite is justified when the current version has produced stable lessons that cannot be incorporated locally without pulling the whole system apart. A rewrite is not justified just because a cleaner abstraction is imaginable.

Before starting a v2, write a short postmortem:

- What did v1 make visible?
- Which ideas were unexpectedly fun?
- Which concepts became load-bearing by accident?
- Which changes required too much vertical surgery?
- Which abstractions earned their place?
- Which abstractions were fantasy architecture?
- What is the smaller v2 thesis?

This is the balance: build fast enough to escape analysis paralysis, but only restart when the old version has taught something concrete.

## Modeling Principle: Encode Truth, Do Not Repeat It

Every important fact in the railroad should exist in exactly one place. Everything else should be derived from that source of truth.

The map should not be one thing for the analyzer, another thing for documentation, another thing for tests, and another thing for a future visualization. The same representation should feed validation, route analysis, generated explanations, debug output, diagrams, and eventually UI rendering.

Likewise, invalid states should be unrepresentable whenever practical. A route should not point to a town that does not exist. A waybill should not reference an unknown good. A consumer should not demand a unit the model cannot describe. A route capacity should not silently use a different unit than demand. The type system should encode these invariants where doing so clarifies the world rather than freezing v1 too early.

This is the C++ appeal as a modeling tool, not as an identity. Strong types, templates, concepts, CRTP, `constexpr` evaluation, and compile-time metaprogramming are useful when they make the structure of the railroad more explicit and harder to misuse. They are not goals by themselves.

The best version of Paper Railroad will feel inevitable: once the representation is right, the analyzer, explanations, tests, diagrams, diagnostics, and later operation layers should all feel like natural projections of the same model.

## Testing Principle: The Proof Is The Product

The Paper Railroad does not need to impress an audience with a polished demo first. The satisfying deliverable is the proof suite: a full run that shows every interesting idea has been captured, exercised, and kept stable.

Every system expansion should have matching tests:

- map validation tests,
- unreachable-town and unknown-good rejection tests,
- producer/consumer balance tests,
- route-load explanation tests,
- bottleneck and slack tests,
- capacity failure tests,
- waybill derivation tests,
- accounting and going-concern tests when that layer exists.

The tests should not just check that the happy path works. They should prove that wrong maps fail for understandable reasons and that plausible false positives do not sneak through. A future UI may be delightful, but the full passing test run is the moment that says the model is actually built.

The tests should also be elegant. A good Paper Railroad test should read like a tiny paper map: set up towns, routes, goods, and demand; run one analysis; assert the meaningful final state or diagnostic. If a test needs a thousand lines of boilerplate, mocking, special cases, or incidental setup, the test infrastructure is failing to express the model.

That means testability must be part of the representation itself. The model should provide small map builders, deterministic analyzers, structured analysis results, inspectable intermediate artifacts, and diagnostics that can be asserted directly. A test should not need to reverse-engineer route loads from logs or poke through private implementation state. If the clean test is hard to write, the representation is probably hiding the concept that the test is trying to prove.

## Layer 1: Static Map Analyzer

This is the HDL equivalent.

No clock. No sim step. No moving train. Just a map and questions about whether the map can work.

### Model Objects

- `Town`: a node on the paper map.
- `Route`: an edge between towns, with distance, optional capacity, and eventually book-derived route burden such as ruling grade, curvature class, bridge/tunnel burden, and maintenance class.
- `Good`: a thing that can be produced, consumed, stored, or transformed.
- `Producer`: a source of a good at a town.
- `Consumer`: a sink for a good at a town.
- `Industry`: a transformation from input goods to output goods.
- `Waybill`: a causal demand and accounting object saying that some quantity of a good must move from origin to destination. Inspired by the book's way-bill discussion, it should eventually support route, revenue, responsibility, and statistics.

### First Questions

- Is every demanded good produced somewhere?
- Is every producer connected to at least one compatible consumer?
- Is every consumer reachable from at least one compatible producer?
- Is total production greater than, equal to, or less than total demand?
- Are there stranded towns, unreachable goods, or disconnected subnetworks?
- Given the demands, what flow must cross each route?
- Which routes are bottlenecks?
- Which routes have slack?
- Is the network convergent, stable, or structurally divergent?

### First Output

The first delightful runnable moment should be a tiny command that reads a paper map and prints an explanation:

```text
Iron Works produces 2 steel/day.
Foundry demands 1 coal/day and 1 ore/day.

Coal from Mine can reach Foundry through:
  Mine -> Junction -> Foundry, distance 5

Required route load:
  Mine -> Junction: 1 coal/day
  Junction -> Foundry: 1 coal/day

Network status:
  Balanced: yes
  Reachable: yes
  Bottleneck: Junction -> Foundry at 100% capacity
```

This is not just reporting. It should be causal. The analyzer should be able to answer why a route is loaded, why a town is underserved, and which waybills contribute to a constraint.

### Book-Derived Route Burden

The route model should eventually capture the civil-engineering idea that a railroad line is not an abstract graph edge. A route is a physical compromise.

Candidate fields:

- `distance`
- `capacity`
- `ruling_grade`
- `curvature_class`
- `bridge_or_tunnel_burden`
- `maintenance_class`
- `capital_burden`

These should not all enter v1 unless they produce useful diagnostics. The first useful version may keep only distance and capacity, but the design should leave room for explanations such as:

```text
Foundry Branch is bottlenecked by ruling grade rather than distance.
Coal demand can be served only by shorter trains or more frequent service.
```

### Book-Derived Report Style

Paper Railroad should prefer report-like output over game-like narration:

- way-bill summary,
- route-load table,
- stranded or underserved towns,
- route burden notes,
- car-accounting notes later,
- going-concern summary later.

## Layer 2: Transport Bandwidth

Once the economy can balance structurally, ask what the railroad must provide.

The core problem becomes network flow with railroad flavor:

- goods create demand,
- demand creates waybills,
- waybills create route load,
- route load creates capacity requirements,
- capacity requirements imply trains, cars, time, or infrastructure later.

### Questions

- How much capacity is required on each route?
- What is the minimum route capacity that satisfies all demand?
- If routes have capacities, what demand cannot be served?
- If multiple routes exist, which route should carry which flow?
- Which new connection would improve the network most?
- Which producer or consumer makes the system unstable?
- Which towns are structurally important?

### Design Rule

Keep this layer mathematical and inspectable. It is acceptable if the implementation uses a standard max-flow or min-cost-flow algorithm later, but the product is the explanation:

- which flow was chosen,
- what constraints forced it,
- which alternatives existed,
- where slack remains,
- where adding capacity matters.

## Layer 3: Going Concern

If the railway works, can it survive as a business?

This is the natural layer above transport feasibility. The railroad is no longer just asked whether goods can move. It is asked whether moving them pays for the railroad.

### Model Objects

- `Rate`: revenue for moving a good over a route, distance, or tariff class.
- `OperatingCost`: cost for route usage, distance, handling, or car-days.
- `CarAccount`: ownership and utilization record for cars.
- `Ledger`: explanation of revenue, cost, utilization, and profit/loss.
- `Investment`: optional capacity expansion, new route, yard, or service improvement.

### Questions

- Which waybills are profitable?
- Which waybills are required for the economy but bad for the railroad?
- Which routes carry traffic but lose money?
- Which towns are economically important but operationally expensive?
- Does the railroad have enough volume to justify a route?
- Does adding capacity increase profit, reliability, or only unused slack?
- Can the railroad remain a going concern under the current rates and costs?

### Historical Mechanics

Use old railroad practice as mechanic inspiration:

- `Waybilling`: every shipment has an origin, destination, good, route, charge, and audit trail.
- `Milling in transit`: a shipment can stop for processing before continuing under one larger commercial movement.
- `Rate differentials`: different routes or towns can be favored by pricing, not just distance.
- `Car accounting`: cars are scarce assets, and their location matters.
- `Demurrage`: slow unloading creates cost and congestion.
- `Interchange`: cars or traffic can cross into another railroad's territory.
- `Empty-car return`: satisfying demand may create repositioning problems.

These should not become bureaucracy for its own sake. Each mechanic must create a more interesting causal question.

## Layer 4: Discrete Operation

Only after static analysis and going-concern viability are interesting should the model acquire time.

At this point, the project can become more like a game or operations sandbox:

- trains move between towns,
- cars carry waybills,
- yards classify cars,
- routes have capacity per time period,
- industries produce and consume on schedules,
- late shipments create pressure,
- economic results accumulate in the ledger.

This layer should inherit artifacts from earlier layers. A train movement should not be an opaque animation. It should be the physical execution of a waybill, a route plan, and a business decision.

## Data Sketch

A first map could be represented in a tiny declarative format:

```yaml
goods:
  - coal
  - ore
  - steel

towns:
  mine:
    produces:
      coal: 2
  quarry:
    produces:
      ore: 2
  foundry:
    consumes:
      coal: 1
      ore: 1
    produces:
      steel: 1
  city:
    consumes:
      steel: 1

routes:
  - from: mine
    to: junction
    distance: 2
    capacity: 2
  - from: quarry
    to: junction
    distance: 2
    capacity: 2
  - from: junction
    to: foundry
    distance: 3
    capacity: 2
  - from: foundry
    to: city
    distance: 4
    capacity: 1
```

The analyzer should derive waybills and route loads from this. Hand-authored waybills can come later.

## First Prototype

Build the smallest analyzer that can answer one satisfying question.

1. Parse a map file.
2. Validate goods, towns, routes, producers, and consumers.
3. Build a graph.
4. Match production to demand for one good.
5. Find reachable producer-consumer pairs.
6. Compute required route loads for a simple routing policy.
7. Print a human-readable explanation.

The first routing policy can be deliberately simple:

- choose shortest path,
- split nothing,
- satisfy demands greedily,
- report where that policy fails.

The goal is not optimality. The goal is to make the model speak.

The first prototype should be intentionally disposable. It should be good enough to discover the shape of the problem, not good enough to become a permanent architecture.

## Success Criteria

The project is working if it can answer questions like these in a way that feels like reading a railroad accountant's map:

- "Why is this route overloaded?"
- "Which town causes this bottleneck?"
- "Can every city get what it needs?"
- "What is the minimum capacity needed on the mountain shortcut?"
- "If the foundry doubles production, what breaks?"
- "Which traffic is profitable?"
- "Is this railroad a going concern?"

The project is failing if the main output becomes an engine, framework, or pile of configuration whose behavior is not visible from a tiny map.

## Guardrails

- Start with one paper map.
- Make every artifact inspectable.
- Prefer one concrete good chain over a generic economic engine.
- Add time only after static causality is satisfying.
- Add trains only after waybills and route loads are meaningful.
- Add accounting only if it explains decisions.
- Let historical detail provide pressure, not paperwork.
- Keep local reasoning: towns do not know the global economy, routes do not know business strategy, and waybills do not know implementation details.
- Prefer a useful v1 over a perfect representation.
- Treat design regrets as input for a later version, not as proof that v1 failed.
- Rewrite only after the current version has taught specific lessons.
- Keep one source of truth for the map, goods, routes, units, capacities, and derived facts.
- Generate explanations, diagnostics, tests, and visualizations from the model instead of maintaining parallel descriptions.
- Use the type system to prevent impossible states when it makes the model clearer, not just cleverer.
- Treat the test suite as a deliverable. Every meaningful model concept should have tests that prove both success and failure behavior.
- Design the representation so tests can express setup, action, and expected state directly.

## Working Name

Possible names:

- Paper Railroad
- Waybill
- Trestle
- Short Line
- Junction
- Car Accountant

`Paper Railroad` is the clearest design name for now.

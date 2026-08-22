# Paper Railroad Train-Book Inspiration

This note captures the parts of *The American Railway* that fit Paper
Railroad. It is a source lens, not a requirements dump. Book detail should move
into Paper Railroad only when it becomes a model field, validation rule,
diagnostic reason, report section, fixture, test expectation, vocabulary
choice, or roadmap boundary.

Paper Railroad should remain a small deterministic planning-office model. The
book enriches that model by making the railroad visible as a managed system of
route constraints, traffic records, car distribution, rates, mail obligations,
maintenance, and statistics.

## Best-Fit Book Lenses

### Way-bills, management, and statistics

The management chapters treat the railroad as something known through records:
way-bills, summaries, rates, car movement, receipts, expenses, and operating
statistics. This strongly fits Paper Railroad's structured-first design.

Project imports:

- a book-derived `Waybill` vocabulary for the causal traffic record currently
  represented by demand and future `TrafficDemand`;
- report sections that look like office memoranda, ledgers, and route-load
  summaries rather than simulator narration;
- durable demand or waybill identifiers so history survives period changes;
- route-load, bottleneck, contribution, and circulation reports that expose
  structured evidence before prose;
- role-labeled diagnostics such as Traffic Office, Engineering Office, Car
  Accountant, Auditor, and Statistics Clerk.

Keep out:

- full waybill paperwork,
- tariff-book detail,
- accounting form reproduction,
- and text-only claims not backed by artifacts.

### Freight-car service and car accounting

The freight-car material is the strongest book support for closed circulation.
Loaded traffic displaces cars. Empty cars, foreign cars, private rules, car
distribution, tracing, interchange, and car accounting are management problems,
not train-simulation problems.

Project imports:

- equipment classes and equipment-equivalent movements instead of individual
  car identities;
- empty balancing flows as first-class transport demand;
- findings for car shortage, car mispositioning, avoidable empty counterflow,
  return-to-owner loss, and equipment blockade;
- pooled versus local planning policies;
- reports that distinguish one-shot loaded movement from recurring circulation.

Keep out:

- individual car histories,
- exact per-diem or mileage accounting,
- yard switching plans,
- and persistent inventory state when a closed normalized cycle answers the
  planning question.

### Civil route burden

The construction and engineering chapters emphasize that a railroad line is not
just a line on a map. Grades, curvature, bridges, tunnels, trestles, road-bed,
maintenance burden, and future operating consequences all shape what traffic
can be sustained.

Project imports:

- optional aggregate route-burden fields such as `ruling_grade_class`,
  `curvature_class`, `bridge_rating`, `tunnel_or_trestle_burden`,
  `roadbed_condition`, and `maintenance_class`;
- capacity factors that let route burden change traffic cost, burden,
  reliability, or eligibility without computing train performance;
- named improvement templates such as bridge strengthening, grade improvement,
  signaling, passing sidings, double tracking, yard expansion, terminal
  modernization, and roadbed improvement;
- investment reports that explain why a point, edge, corridor, route-family,
  equipment-class, or policy action matches the diagnosed constraint.

Keep out:

- survey math,
- exact bridge design,
- siding length,
- signal spacing,
- rail weight formulas,
- locomotive horsepower curves,
- and construction management.

### Rates, pools, and business relations

The business and statistical material connects railroad planning to rates,
competition, pooling, long-haul versus local traffic, special rates,
regulation, public policy, and the gap between traffic volume and railroad
profit.

Project imports:

- separation of destination value, railroad rate, subsidy, movement cost, and
  recurring support cost;
- rate policies that can change demand, route choice, town outcomes, railroad
  revenue, and actor benefit;
- pooling and coordination agreements as visible policy artifacts;
- findings where physically possible service is unattractive, socially
  important service is unprofitable, or rates reshape which traffic survives.

Keep out:

- comprehensive tariff law,
- open-ended public-policy simulation,
- full competitive strategy,
- and finance systems before small scenarios prove the need.

### Mail and public-service traffic

The mail-service material fits Paper Railroad when mail acts as policy traffic:
priority movement, route coverage, subsidy or contract revenue, minimum
service, specialized equipment, and public value separated from ordinary
freight profit.

Project imports:

- mail, express, military, or essential service as traffic classes with
  explicit priority, equipment, subsidy, and service constraints;
- fixtures where policy service sustains an otherwise marginal route or
  displaces ordinary freight;
- reports that separate railroad profit from public value.

Keep out:

- mail sorting mechanics,
- clerical workflow,
- and passenger timetable modeling.

### Shocks, fragility, and overdevelopment

The book's statistical and business framing is useful for scenario pressure:
directional imbalance, empty trains, overbuilt lines, maintenance burden,
competition, public obligations, and the difference between gross traffic and
net earning power.

Project imports:

- speculative-branch scenarios where construction is attractive only under
  induced demand, subsidy, or an anchor industry;
- shared-trunk scenarios where every branch is locally attractive but jointly
  infeasible;
- shock scenarios that strand equipment, close routes, alter demand, or force
  emergency pooling;
- reports that identify wrong investment, unused capacity, blockade, and
  maintenance-cost drag.

Keep out:

- broad economic history simulation,
- unbounded actor forecasts,
- and multi-decade finance until earlier layers are stable.

## Paper Railroad Phase Hooks

- Design/refactor phases should make the book lens explicit in project docs and
  keep `Waybill` as the preferred period vocabulary for the causal traffic
  record, even if the implementation name remains `Demand` or `TrafficDemand`
  during refactors.
- Economic separation should draw from the book's distinction among value,
  rates, cost, receipts, public obligation, and railroad earning power.
- Equipment-compatible and closed-circulation phases should use the
  freight-car-service lens for car distribution, empty return, foreign-car
  rules, and pooled planning.
- Heterogeneous capacity should use the civil-route and service-priority
  lenses: grade, curvature, bridge restriction, terminal burden, local freight,
  mail, passenger, and empties can all consume capacity differently.
- Historical fixture phases should start with small book-inspired worlds:
  empty cars crossing, mail-supported mountain branch, shared trunk,
  speculative coal branch, two grain towns, and flood/emergency pooling.
- Named-improvement phases should preserve action identity from diagnosis to
  report so the prose can truthfully say "double-track", "expand yard",
  "strengthen bridges", "improve signaling", "purchase hoppers", or "pool
  equipment" only when that template was selected.

## Promotion Checklist

Before importing book material into Paper Railroad, answer yes to at least one:

- Does it change what traffic can move?
- Does it change railroad revenue, subsidy, movement cost, or recurring support
  cost?
- Does it change equipment circulation or capacity consumption?
- Does it alter service survival, investment ranking, actor benefit, or policy
  interpretation?
- Does it produce a structured diagnostic, report section, fixture, or test
  assertion?

If not, leave it in source notes as period texture.

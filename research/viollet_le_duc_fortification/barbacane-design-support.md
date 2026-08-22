# Barbacane Design Support

This document translates the paired book research into project-shaping
guidance. It is not yet Barbacane's canonical design. Once the project is
created, its repository should own the active design and scenario research.

## Project Thesis

> Barbacane is an executable model of the siege engineer's art. Given terrain,
> strategic objectives, resources, contemporary means, and an adversary model,
> it produces and explains a defensible fortification plan. Val d'Ohet is the
> canonical world in which that reasoning is tested across successive eras of
> attack and defense.

## Point Of View

The project fantasy is the immortal siege engineer implicit in
Viollet-le-Duc's work: the same analytical intelligence returns to one place,
reads each new situation, and constructs what the present conditions require.

The pleasure should come from three related acts:

1. Seeing the engineer's spatial argument.
2. Testing that argument against an adversarial interpretation.
3. Reading the design and its consequences as an illustrated chronicle.

The first vertical slices emphasize the first act, prove it through the
second, and report it in the form of the third.

## Fundamental Shape

The central executable object should be a commission:

    Commission
      site
      protected objectives
      inherited works
      defender capabilities
      attacker model
      period means and doctrine
      resources and deadlines
      assumptions and uncertainty

The engineer transforms a commission into a proposal:

    Proposal
      plan
      construction allocation
      operational concept
      predicted attack
      claims and evidence
      weaknesses and tradeoffs
      rejected or dominated alternatives

An evaluation places that proposal against one or more attacker responses:

    Evaluation
      attacker interpretation
      candidate approaches
      defensive effects
      failure and fallback states
      counterfactual comparisons
      unresolved risks

A study packages the commission, proposal, evaluation, and report-ready
evidence. Approach remains the tactical spine of the spatial analysis;
ouvrage remains a useful term for a constructed work.

## Model Boundaries

### Geometry owns

- coordinates, transforms, and units;
- points, segments, paths, regions, and topology;
- intersection, containment, distance, offset, and visibility primitives;
- derived regions and geometric witnesses;
- explicit tolerance and invalid-geometry behavior.

Geometry should not know what a barbican, bow, mine, or demi-lune is.

### Terrain owns

- ground regions and elevation representation;
- slope, water, soil, vegetation, and traversability;
- roads, crossings, commanding ground, and masked areas;
- suitability for movement, construction, excavation, or battery placement.

### Means and doctrine own

- weapons and their deployment requirements;
- construction methods and material choices;
- attack and defensive actions;
- observation and protection capabilities;
- period-specific legal and plausible combinations;
- rules by which geometric relationships acquire tactical meaning.

### Works own

- built features and their components;
- material, dimensions, orientation, access, and internal connection;
- inherited, modifiable, removable, proposed, damaged, and destroyed state;
- operational capabilities exposed by construction.

### Analysis owns

- approaches and candidate actions;
- obstruction, diversion, exposure, support, and fallback claims;
- counterfactual comparison;
- structured evidence and limitations.

### Reporting owns

- document structure;
- maps, sections, profiles, legends, and annotations;
- prose assembled from evidence;
- stable links among claims, figures, assumptions, and source notes.

The renderer should not recompute analysis.

## Period Profile

Period should be encoded through capability-bearing data, not inheritance by
historical style and not a single year field.

An era profile may include:

- movement classes and deployment space;
- offensive weapons and effects;
- defensive weapons and effects;
- protective equipment and directional coverage;
- siege actions and construction prerequisites;
- work types and materials available;
- labor and construction rates;
- observation and communication methods;
- logistics and garrison assumptions;
- doctrine used to rank risks and tradeoffs.

Named profiles such as "La Roche-Pont, twelfth century" are scenario
conveniences assembled from these facts. They should not grant a hidden
"build barbican" rule.

## Plan Generation

The design agent should begin as an inspectable deterministic search process,
not an opaque generative model.

A first constrained designer can:

1. Derive candidate approach corridors.
2. Diagnose one represented weakness.
3. Choose from a very small period-valid palette.
4. Generate parameterized placements.
5. Reject invalid and unaffordable candidates.
6. Evaluate surviving candidates across visible dimensions.
7. Return a Pareto set or explicitly doctrinal choice.
8. Explain why the selected plan addresses the diagnosed weakness.

An LLM may eventually help formulate hypotheses or edit prose, but it should
not be the source of geometry, tactical effects, or unsupported rationale.

## Evaluation Dimensions

Avoid a single unexplained fortress score. Preserve dimensions such as:

- construction labor, time, and material;
- garrison and weapon demand;
- approach actions added or made harder;
- delay or attacker work required;
- attacker exposure by action and segment;
- observation and dead ground;
- mutual-support relationships;
- number and quality of fallback states;
- protected friendly movement;
- vulnerability to represented attacker counters;
- dependence on a single work;
- uncertainty and assumptions;
- consequences of removing or losing each work.

Doctrine may rank or constrain these dimensions. Reports should still show
them separately.

## Evidence Contract

Every tactical claim should carry:

- stable claim identifier;
- subject work, area, or action;
- effect type;
- applicable attacker and defender capabilities;
- preconditions;
- geometric facts and witnesses;
- tactical derivation;
- source facts and model assumptions;
- confidence or uncertainty where appropriate;
- counterfactual comparison;
- limitation or known unmodeled counter;
- diagram instructions or references.

Example claim shape:

    claim: barbican-delays-gate-approach
    effect: adds_required_action
    subject: north-barbican
    approach: plateau-to-main-gate
    required_action: capture_or_bypass_outer_work
    evidence:
      - direct route intersects closed outer enclosure
      - bypass routes are outside traversable region
      - inner gate remains disconnected after outer capture
    limitation:
      - assumes no practicable breach through the eastern curtain

Tests inspect this evidence. The HTML report explains it.

## Canonical World And Scenario Family

Val d'Ohet should be a versioned world with persistent terrain and successive
states. A scenario references:

- a world terrain revision;
- a settlement and inherited-work state;
- an era profile;
- a commission;
- attacker and defender knowledge;
- source provenance;
- project-introduced assumptions.

The terrain reconstruction itself should be versioned because future work may
improve scale, elevation, or interpretation without rewriting what the source
actually depicts.

## Recommended First Vertical Slice

### La Roche-Pont barbican study

Input:

- simplified 2D interpretation of the northern castle approach from Figures 35
  and 36;
- main gate, bailey, inner castle entrance, adjacent towers, and barbican;
- one attacker movement class and one directional projectile capability;
- explicit assumptions about shields, walls, passage, and range.

Analysis:

- validate the work geometry;
- identify the direct gate approach;
- segment passage into successive defensive states;
- show how the angled entry changes attacker orientation;
- identify areas supported from the bailey or towers;
- compare the position with and without the barbican;
- explain what remains true after the barbican is captured.

Artifact:

- deterministic HTML with inline SVG;
- source plate and reconstruction provenance;
- before-and-after plans;
- numbered claims linked to diagram evidence;
- explicit assumptions and limitations;
- short siege excerpt or paraphrase connecting analysis to the Fourth Siege.

This first study proves analysis and reporting. It does not yet generate the
barbican.

## First Generative Milestone

After the analyzer can explain the source design, give a constrained engineer
the pre-design commission:

- protect the gate and preserve sortie/retreat;
- face the expected plateau approach;
- use a fixed work palette and resource allowance;
- obey period construction and weapon constraints;
- do not expose the historical figure as an answer template.

Let it produce several valid proposals, evaluate them, and select one under an
explicit doctrine. Then compare its proposal with Viollet-le-Duc's design.

The comparison should ask:

- Did both plans diagnose the same approach?
- Did they create the same tactical relationships by different geometry?
- Which source assumptions were absent from the commission?
- Did the generated plan exploit a loophole in the model?
- Which missing capability or constraint would change the result?

Similarity to the historical/source plan is interesting evidence, not the
definition of correctness.

## Later Book-Driven Studies

These are candidate vertical slices, not a committed roadmap.

### Oppidum

- Choose a refuge perimeter under labor and material constraints.
- Exercise terrain, simple approaches, palisade, ditch, projecting towers, and
  fire vulnerability.

### Mine and countermine

- Extend the world below the surface.
- Exercise hidden paths, excavation time, acoustic evidence, uncertain belief,
  and interception.

### Keep and layered castle

- Allocate resources among outer enclosure, bailey, keep, postern, and internal
  barriers.
- Evaluate autonomy, fallback, defender movement, and failure sequence.

### Fire-artillery transition

- Present inherited high masonry and a new bombard capability.
- Let the engineer choose among adaptation, earth backing, new artillery
  positions, sacrificial outworks, and abandonment.

### Demi-lune and covered approach

- Represent batteries, saps, directional cover, ditches, covered way, and
  overlapping defensive fires.
- Evaluate whether every work is supported and what must be suppressed before
  the attacker advances.

### Long-range artillery

- Hold the strategic objective steady while increasing range and destructive
  effect.
- Test whether the engineer abandons inherited close geometry for detached
  works and distributed fire.

## Report Progression

Reports can grow in the same vertical slices:

1. Static engineering plate with claims.
2. Before-and-after design memorandum.
3. Alternatives and tradeoff comparison.
4. Attacker's counter-analysis.
5. Day-by-day or phase-by-phase siege chronicle.
6. Multi-era annal showing why each inherited design changed.

The final form should distinguish world truth, actor observation, actor
belief, decision rationale, action, and outcome.

## Verification Suggested By The Books

- Transform invariance for geometry where orientation is transformed with the
  scenario.
- Full, partial, tangent, and absent coverage fixtures.
- Gate sequences that remain closed until every required transition occurs.
- Support relationships that disappear when their weapon, opening, or line of
  action is removed.
- Counterfactual feature-removal tests.
- Period tests proving unavailable works and actions cannot be selected.
- Resource tests proving unaffordable plans are rejected.
- Scenario tests showing a changed weapon profile changes the preferred plan.
- Stable evidence identifiers and complete report cross-references.
- Deterministic proposal ordering and report output.

## Primary Failure Modes

- Building a generic geometry framework before one source claim is explained.
- Encoding named castle forms without their tactical preconditions.
- Letting a universal score hide incompatible doctrines and tradeoffs.
- Treating the source plan as ground truth rather than a reasoned proposal.
- Generating attractive prose that outruns structured evidence.
- Making the period cosmetic.
- Modeling weapon range while ignoring deployment, protection, labor, and
  observation.
- Expanding into a full siege before static effects and fallback states are
  credible.
- Allowing Barbacane-specific vocabulary to leak into a general geometry
  kernel.

## Project Checkpoint Questions

- Can a reader understand the claimed defensive effect without reading code?
- Can a test identify exactly which assumption makes the claim true?
- Does changing ground or means change the plan for a visible reason?
- Can the attacker challenge the plan rather than merely consume hit points?
- Does the source comparison reveal a missing concept?
- Has the current vertical slice earned the next spatial or temporal layer?

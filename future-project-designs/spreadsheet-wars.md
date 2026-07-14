# Spreadsheet Wars Design Doc

## Core Question

Can naval operations problems be studied as small probabilistic decision models
instead of real-time tactical simulations?

The seed is not "build CMANO" and not "make an RTS with ships." The seed is the
analytical shape underneath naval tactics: detection, scouting, contact
confidence, salvo size, defensive saturation, counter-salvo timing, magazine
depth, attrition, uncertainty, and decision delay.

The goal is to build a naval operations analysis sandbox: a set of executable
thought experiments that answer tactical decision questions with tables,
distributions, probability models, sensitivity sweeps, and simple charts.

The guiding rule is:

```text
Do not simulate the battle. Analyze the decision.
```

Or, in the more playful version:

```text
No tiny ships unless they are made of probability.
```

## Fantasy

I can define a small naval decision problem:

- an incoming salvo,
- a defensive system,
- uncertain kill probabilities,
- soft-kill effects,
- magazine limits,
- mission-kill and catastrophic thresholds,
- a policy choice or timing assumption.

Then the project can show:

- the assumptions,
- the expected result,
- the full outcome distribution,
- the probability of mission kill,
- the probability of catastrophic loss,
- the sensitivity to each major input,
- whether a closed-form estimate and Monte Carlo simulation agree.

The satisfying output is not an animated battle. It is a table or chart that
makes a tactical structure visible.

Example questions:

- How large does a salvo need to be before it saturates a defense?
- What is the probability of mission kill, not just the expected number of hits?
- How much does detection probability matter compared with missile
  effectiveness?
- What is the value of reducing decision delay?
- How does uncertainty in `p(k)` change the outcome distribution?
- When does preserving magazine depth matter more than maximizing the first
  strike?
- How much scouting is enough before committing a salvo?
- What is the risk of firing on ambiguous contact information?

## Fundamental Shape

The central object should not be a ship, missile, sensor, or map contact. The
project should be organized around declared analytical decision problems.

For now, I can think of each problem as an engagement model: a small, explicit
bundle containing:

- explicit assumptions,
- uncertain parameters,
- one or more policy choices,
- an evaluation method,
- outcome distributions,
- diagnostics explaining which assumptions drove the result.

The model should be small, inspectable, and reproducible. Randomness is allowed
because probability is the subject, but every Monte Carlo run should be seeded
and replayable.

## Why This Fits

Spreadsheet Wars matches the small-world philosophy if it stays analytical.

- It exposes a hidden system: how naval tactical outcomes depend on information,
  timing, uncertainty, and saturation.
- It can start with one clean model before any broader simulation exists.
- It naturally supports causality through assumptions, traces, posterior
  distributions, and sensitivity tables.
- It is mathematically chewy without requiring a huge platform database.
- It connects to the paper railroad idea: analyze the network or decision
  structure rather than simulating every moving object.
- It is historically flavored without needing to recreate historical battles.

The old failure mode to avoid is scope expansion. A naval simulation can absorb
infinite detail: platforms, weapons, sensors, weather, command doctrine,
geography, pathfinding, communications, emissions control, and real-time orders.
This project should stay closer to a notebook, model library, or dashboard.

## Non-Goals

- Do not build a real-time tactics game.
- Do not build a CMANO-like platform simulation.
- Do not start with animated tactical displays.
- Do not build a huge weapons, sensor, or ship database.
- Do not model individual platform maneuver unless it directly supports an
  analytical question.
- Do not start with doctrine scripting, pathfinding, or AI commanders.
- Do not recreate historical battles as the primary goal.
- Do not hide the model behind cinematic output.
- Do not treat `p(k)`, detection probability, or soft-kill effectiveness as
  magic constants when uncertainty is the interesting part.

The first version should not have a map, clock, real-time control loop, unit
micromanagement, task force AI, or sensor geometry engine.

## V1 Thesis

The smallest worthwhile v1 is a salvo outcome model.

Given an incoming salvo, defensive shots, defensive kill probability, soft-kill
effect, hit probability, and damage thresholds, compute the distribution of
outcomes.

V1 should compare three views of the same problem:

1. A closed-form or binomial estimate.
2. A seeded Monte Carlo simulation.
3. An uncertain-parameter model where `p(k)` is a probability distribution.

The first project win is not a perfect naval model. It is a model that can show
the difference between:

```text
Expected leakers: 2.1
```

and:

```text
P(no hits):      0.31
P(minor damage): 0.27
P(mission kill): 0.34
P(catastrophe):  0.08
```

That distinction is the project thesis in miniature.

## First Runnable Moment

A tiny command reads one scenario file and prints an outcome report:

```text
$ spreadsheet-wars run examples/simple-salvo.yaml

Scenario: Simple Salvo

Incoming missiles:        16
Defensive shots:          12
Defense p(k):             Beta(18, 6)
Soft-kill leakage factor:  0.85
Hit probability:          0.65
Mission kill threshold:   2 hits
Catastrophic threshold:   5 hits
Monte Carlo trials:       100000
Seed:                     12345

Outcome distribution:
  P(no hits):          0.31
  P(minor damage):     0.27
  P(mission kill):     0.34
  P(catastrophic):     0.08

Expected leakers:      3.42
Expected hits:         2.22
```

The output should also make the assumptions visible. A report that does not
state its assumptions is not useful for this project.

## Model Objects

Initial v1 objects:

- `Salvo`: incoming weapons or shots.
- `DefenseLayer`: defensive capacity and kill model.
- `KillProbability`: either a fixed probability or a distribution.
- `SoftKillEffect`: reduction in effective incoming threat or hit probability.
- `LeakerDistribution`: probability distribution over missiles that survive
  defenses.
- `HitDistribution`: probability distribution over hits after leakage.
- `DamageThresholds`: rules for no damage, minor damage, mission kill, and
  catastrophic loss.
- `OutcomeDistribution`: named outcome probabilities and summary statistics.
- `SensitivitySweep`: repeated evaluation over one or two changed parameters.
- `Scenario`: serializable assumptions for one executable thought experiment.

Later objects, only after the salvo core earns them:

- `ContactBelief`: belief that a target is present, classified, or worth
  engaging.
- `SensorObservation`: detection, non-detection, false alarm, or ambiguous
  report.
- `ScoutAllocation`: distribution of search effort across sectors.
- `MagazineState`: remaining offensive and defensive shots.
- `Policy`: choice rule such as fire now, wait for confidence, preserve
  magazine, or re-attack.
- `DecisionDelay`: time cost that changes information, vulnerability, or salvo
  timing.

## Probability Shape

The project should use probability as the object of study, not just as a source
of random outcomes.

Useful v1 modeling tools:

- binomial models for fixed kill or hit probability,
- beta distributions for uncertain probabilities,
- beta-binomial models or posterior predictive sampling,
- Monte Carlo simulation for composed models,
- seeded random generation for replayable examples,
- sensitivity sweeps for understanding parameter importance.

The key design habit is to represent uncertainty directly. A fixed `p(k)` is
useful as a baseline, but many interesting questions come from treating `p(k)`
as an uncertain belief.

Example:

```text
Defense p(k) = 0.75
```

is a different model from:

```text
Defense p(k) ~ Beta(18, 6)
```

Both may have the same mean. They do not necessarily produce the same tactical
risk profile.

## Candidate Modules

The project can grow as a collection of small standalone analytical ponds:

- salvo exchange,
- layered defense,
- detection and contact confidence,
- scout allocation,
- counter-salvo timing,
- magazine depletion,
- re-attack and campaign-day analysis,
- simple policy comparison under uncertainty.

Each module should be able to stand alone. A weekend-sized version of any module
should still feel satisfying.

## Possible Growth Path

### Phase 1: Salvo Pond

Deliverable:

- one scenario file,
- one command that evaluates it,
- one printed distribution,
- one test suite proving fixed-probability salvo behavior.

Verification:

- deterministic tests for edge cases such as zero incoming missiles, no
  defensive shots, perfect defense, impossible defense, and threshold boundaries,
- comparison tests between closed-form output and Monte Carlo output within a
  documented tolerance,
- report snapshot or structured-output tests for the first scenario.

Checkpoint:

- Does the report make the tactical structure clearer than a single expected
  value?

### Phase 2: Uncertain Kill Probability

Deliverable:

- beta-distributed defensive `p(k)`,
- posterior predictive evaluation,
- comparison of fixed-mean and uncertain-parameter models.

Verification:

- tests for beta parameter validation,
- seeded Monte Carlo tests,
- known small-case comparisons,
- documented examples showing how uncertainty changes tail risk.

Checkpoint:

- Does uncertainty around `p(k)` visibly change mission-kill or catastrophic
  risk?

### Phase 3: Sensitivity Sweeps

Deliverable:

- table output over salvo size, defensive capacity, and `p(k)` assumptions,
- simple chart or CSV export if useful.

Verification:

- tests for sweep grid construction,
- tests for monotonic sanity properties where they are mathematically valid,
- stable fixture output for one small sweep.

Checkpoint:

- Can the model answer "what matters most?" without a dashboard?

### Phase 4: Layered Defense

Deliverable:

- multiple defensive layers such as hard-kill, soft-kill, and terminal defense,
- inspectable intermediate distributions between layers.

Verification:

- tests that each layer composes deterministically,
- tests for layer order and saturation behavior,
- examples showing where layered defense differs from one equivalent-looking
  aggregate probability.

Checkpoint:

- Does layering reveal something that the single-layer model hides?

### Phase 5: Contact Belief

Deliverable:

- a tiny belief-state model for target presence, class, or engagement value,
- Bayesian updates from detection, non-detection, false alarm, or ambiguous
  reports.

Verification:

- tests for posterior updates,
- tests for impossible and low-information observations,
- examples comparing fire-now versus wait-for-more-information policies.

Checkpoint:

- Does the model make information value visible without becoming a sensor sim?

## Implementation Notes

Python is the likely first implementation language because the domain naturally
fits probability tooling, table output, plotting, notebooks, and fast model
iteration.

The first repo should still be a tested CLI/model library rather than only a
Jupyter notebook. Notebooks are good presentation surfaces, but a deterministic
CLI and test suite will keep the model honest.

Probable active-repo shape:

```text
spreadsheet-wars/
  README.md
  docs/
    design.md
    roadmap.md
  src/
    spreadsheet_wars/
      salvo.py
      distributions.py
      sweep.py
  tests/
    test_salvo.py
    test_distributions.py
  examples/
    simple-salvo.yaml
```

Every model should answer:

1. What assumptions went in?
2. What distribution came out?
3. Which assumption was the outcome most sensitive to?

## Risks

### Simulation Drift

The most likely failure mode is accidentally building a tactical simulation
engine. If work starts requiring maps, movement, unit AI, sensor geometry, or
real-time orders, shrink the model back to the question being analyzed.

### Database Gravity

Naval topics invite giant lists of real platforms and weapons. V1 should use
fictional or abstract parameters. Real-world flavor can be added in examples
later, but databases should not be the foundation.

### False Precision

The project should not pretend that made-up `p(k)` values are truth. It should
make assumptions explicit, vary them, and show how outcomes change.

### Notebook Sprawl

Notebooks can become untested essays. They should be downstream of tested model
code, not the only implementation.

## V2 Triggers

A v2 or active repo is worth starting when the first salvo design has enough
clarity to support:

- one canonical scenario file,
- one deterministic report format,
- one closed-form calculation,
- one Monte Carlo calculation,
- one uncertain-parameter extension,
- one sensitivity sweep,
- tests that prove the model rather than just print numbers.

Detection, scouting, and magazine policy should wait until the salvo pond has
produced at least one concrete design regret.

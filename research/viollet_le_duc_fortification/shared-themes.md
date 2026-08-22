# Shared Themes

## Paired Reading

Read together, the books present fortification as adversarial design rather
than a sequence of architectural styles.

*Castles and Warfare in the Middle Ages* supplies a comparative vocabulary of
mechanisms. *Annals of a Fortress* places mechanisms into one persistent world
and shows an enemy responding to them. The first asks how works operate; the
second asks whether a particular arrangement survives contact with an
intelligent opponent and changing technology.

The shared hidden system is:

    means + ground + objective + resources + beliefs
        -> plan
        -> anticipated attack
        -> defensive effects and liabilities
        -> adversarial countermeasure
        -> changed position
        -> revised plan

This loop, rather than any one wall or period, is the conceptual foundation
for Barbacane.

## The Invariant Problem

Across periods, the defender is trying to allocate limited means so the
attacker cannot cheaply convert access into possession.

The most stable questions are:

- What must remain protected or usable?
- From where can an attacker approach?
- What must the attacker bring, build, cross, suppress, or destroy?
- Where is the attacker visible or exposed while doing so?
- Which defensive work can intervene?
- What protects that defensive work?
- What state remains if it is bypassed, suppressed, breached, or captured?
- How much time, labor, material, force, and information does each transition
  consume?

The answers change with the period. The question structure does not.

## Period As Capabilities

A period profile should describe available means rather than assign a label
such as "medieval" or "Vauban."

Useful dimensions include:

| Dimension | Examples of differences |
| --- | --- |
| Movement | Foot, horse, wagon, engine, gun, protected gallery |
| Access | Ladder, bridge, fill, ram, breach, sap, mine |
| Direct action | Hand weapons, bow, crossbow, engine, smoothbore cannon, rifle |
| Protection | Shield, mantelet, testudo, gabion, trench, parapet, casemate |
| Observation | Direct sight, elevated watch, scout, acoustic mine detection |
| Construction | Earth, timber, masonry, revetment, field improvisation |
| Destruction | Fire, impact, undermining, bombardment, explosive projectile |
| Organization | Levy, retinue, trained engineer, artillery train, formal siege corps |
| Communication | Shout, signal, messenger, planned timetable, command network |
| Sustainment | Food, water, ammunition, repair material, draft animals, relief |

Capabilities should carry preconditions and consequences. A gun requires a
position, field of fire, platform, crew, and supply. A mine requires protected
origin, excavatable material, time, support, and a target foundation. A
mantelet protects selected directions and weapon classes while changing speed
and space requirements.

This avoids making period a cosmetic modifier and allows historically
plausible novelty: an agent can recombine available means without selecting
from a fixed catalog of named castle styles.

## Terrain As Active Constraint

Both books insist that ground participates in the design.

Terrain influences:

- which approaches exist;
- which routes can support troops, engines, or artillery;
- where an attacker can assemble or establish batteries;
- what can be observed or masked;
- how water, slope, and soil delay movement or construction;
- where a mine can begin and proceed;
- how defenders move, sortie, retreat, and receive supply;
- whether a work commands surrounding ground or is commanded by it.

Terrain should not be a painted background beneath a work. A generated plan
is evidence that the agent has read the ground only if changing the ground can
change the plan for an explainable reason.

## Approach As A Transformation

An approach is more than a route polyline. It is the attacker's evolving
ability to bring an action to a target.

An approach can be:

- physically blocked;
- redirected;
- lengthened;
- narrowed or congested;
- exposed to observation or fire;
- protected from selected threats;
- made suitable for one weapon and unsuitable for another;
- advanced by constructing a bridge, fill, trench, battery, gallery, or mine;
- denied when a supporting work remains active;
- reopened when that work is suppressed.

This suggests representing siege operations as transformations of an access
state. Ditch filling, battery construction, breach creation, and capture of an
outwork are not isolated events; they change which subsequent actions are
available.

## Mutual Support

The books' most durable spatial principle is that a defense should not rely on
isolated passive resistance. Works gain value through relationships.

A support relation should identify:

- supporter and supported work;
- attacker action or approach being opposed;
- capability used to support;
- geometric condition;
- operational preconditions;
- what breaks the relationship;
- whether support is reciprocal.

For example, "tower A supports curtain B" is incomplete. A defensible claim
might be:

> Tower A can direct lateral crossbow fire along the exterior foot of curtain
> B while its eastern opening remains operable; this denies unshielded wall
> work but does not prevent a roofed gallery from approaching outside the
> represented range.

That form is simultaneously testable and reportable.

## Defense In Depth

Layered defense is not just concentric shape. It preserves useful choices as
the position changes.

Important properties include:

- outer loss does not open an uninterrupted path to the protected asset;
- defenders can retreat without sharing the attacker's route;
- inner works can act upon a captured outer area;
- breaches can be isolated or retrenched;
- supplies and command survive the loss of peripheral works;
- the attacker must reposition, expose new equipment, or repeat preparation;
- the garrison can choose where continued defense is worth its cost.

This is naturally modeled as a state graph. Nodes are defensible states;
attacker actions create transitions; works alter the availability, cost, and
consequence of those transitions.

## Time And Work

Fortifications frequently win by consuming time rather than remaining
permanently unbroken.

Time enters through:

- original construction;
- readiness and maintenance;
- deployment of engines or guns;
- excavation, fill, and bridging;
- bombardment and repair;
- mine and countermine;
- movement through constrained passages;
- rest, watches, supply, and relief;
- rebuilding or temporary retrenchment during attack.

An initial static analyzer can express effort or required actions without
simulating a clock. Later discrete-time siege models can turn those actions
into schedules, interruptions, and races.

## The Plan Is A Hypothesis

A generated plan predicts an attacker:

- likely direction;
- likely equipment;
- acceptable losses;
- preferred sequence;
- ability to observe hidden conditions;
- willingness to spend time;
- response to resistance and uncertainty.

The plan should expose those predictions. An attacking agent can then evaluate
the plan by finding a cheaper, safer, faster, or unexpected counter-approach.

This is more interesting than optimizing one defensive score. It allows a
plan to be coherent but wrong because its adversary model was wrong.

## Explanation As Evidence

Both books use diagrams to make prose claims inspectable. Barbacane can
formalize that relationship.

Every important claim should preserve:

- subject and claimed effect;
- conditions under which the effect holds;
- source facts and model assumptions;
- geometric witnesses or measurements;
- tactical interpretation;
- counterexample or limitation;
- diagram elements needed to inspect it;
- stable identifiers linking evidence to prose.

The report then becomes an executable interpretation of structured evidence,
not a second analysis written by hand.

## Productive Tensions

The paired books create several tensions worth preserving rather than solving
with a universal score:

- permanent strength versus adaptability;
- protection versus observation and action;
- concentrated defense versus extended mutual support;
- stronger outer work versus safe fallback after its capture;
- height and command versus artillery exposure;
- short perimeter versus room for depth and batteries;
- economy of construction versus economy of defenders;
- historical doctrine versus novel response;
- source reconstruction versus generated alternative;
- correct world state versus an actor's partial belief.

These are candidate report dimensions and agent tradeoffs.

## Shared Research Questions

- What is the smallest capability vocabulary that produces recognizably
  different period plans?
- Which tactical predicates can be defined in exact geometry and which require
  doctrine or simulation?
- Can support and fallback be evaluated without simulating combat?
- Can the same evidence structure explain a surface fire field, a gate
  passage, and a mine-countermine relation?
- How should uncertainty in a source plate propagate into a generated claim?
- Can an agent explain why a named historical form emerged without being
  allowed to select that form by name?
- Can Val d'Ohet function as a longitudinal test world while unrelated sites
  test generality?
- What plan differences are caused by weapons, and what differences are caused
  by organization, labor, or strategic objective?

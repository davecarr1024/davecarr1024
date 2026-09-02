# Spring Body Lab Design Doc

## Core Question

Can a small, deterministic browser laboratory make ordinary differential
equations, numerical integration, constraints, fracture, and emergent
structural failure understandable through an inspectable physical world?

The project starts with the analytical nugget rather than the eventual game:

> How do I define an ODE, implement several solvers, and test when their
> approximation deserves trust?

Its eventual payoff is a small breakable-structure game: a ram, catapult, or
later trebuchet applies force to a weakly bonded wall, whose deformation,
cracking, and collapse follow from the model rather than a scripted animation.

## Working Name

`Spring Body Lab` is a descriptive shelf name. A promoted project should earn
a short proper name once its first playable breach scenario has a distinct
character.

## Fantasy

I begin with one mass on a spring and can see its exact and numerical
trajectories diverge. I choose a timestep that makes explicit Euler gain
energy, then see why a different integrator behaves better. I couple many
points into a triangulated body, remove support beneath an opening, and watch
loads concentrate, bonds fail, and a section of wall fall.

At every tick, the lab can answer why:

```text
tick 348:
  contact: ram head against wall face 12
  contact response: distributed to structural points 27, 31, 44
  bond 27--31: tensile strain 0.34; limit 0.25; broke
  component 4: detached after the break
  remaining support: bending load increased; component fell
```

The eventual game is not a historically accurate structural-engineering
system. It is a consistent, replayable model in which a player can learn the
weak structural path through a tiny fortification by applying force.

## Fundamental Shape

The core is a pure ODE plus a replaceable numerical integrator:

```text
State y
Derivative f(t, y) -> dy/dt
Integrator.step(f, t, y, dt) -> next y
```

For particle systems, state contains particle positions and velocities.
The derivative accumulates gravity, spring/bond forces, damping, and later
contact forces or corrections.

The simulation must remain distinct from its browser presentation:

```text
scenario + parameters
        |
deterministic headless simulation
        |
snapshot, trace, diagnostics, fracture/contact events
       / \
tests and artifact checks   interactive browser renderer
```

The browser is an inspector and a shareable learning surface, not the source
of simulation truth. The same named scenario and scripted input trace must
replay headlessly.

## Shared ODE and Math Basis

Spring Body Lab shares a deliberately small foundation with
`rigid-body-lab.md`: vector/rotation math, ODE state and derivative contracts,
integrators, deterministic scenarios, traces, diagnostics, and analytic-test
helpers. It must not grow a universal body/collision/entity framework. The
spring lab owns particles, bonds, fracture, and deformable collision geometry;
the rigid lab owns poses, inertia, shapes, contacts, impulses, and joints.

The shared boundary can begin as modules in one learning repository. It should
be extracted only after both concrete labs demonstrate that it is real.

## Mathematical Learning Spine

The project should grow one interpretable differential-equation system at a
time:

| Stage | System | What becomes visible |
| --- | --- | --- |
| 1 | Constant velocity | Position is the integral of velocity. |
| 2 | Gravity | Velocity is the integral of acceleration. |
| 3 | One spring | A second-order ODE creates oscillation. |
| 4 | Damped spring | Energy leaves the system. |
| 5 | Coupled masses | Local laws form a larger system of ODEs. |
| 6 | Stiffness sweep | Timestep and solver stability become tangible. |
| 7 | Constraints | Some relationships are better solved than expressed as ever-stiffer forces. |
| 8 | Contact and fracture | Continuous dynamics meets discontinuous structural events. |

Initial integrators should include explicit Euler, semi-implicit Euler,
midpoint/RK2, and RK4. Explicit Euler remains valuable even where it fails:
its energy gain and instability are part of the lesson. A later
constraint-oriented chapter may compare a force-based model with PBD/XPBD.

## Bodies, Materials, and Failure

A deformable body is a discrete material model, not a universal soft-body
primitive. Its material behavior comes from:

- point placement and mass distribution;
- triangle connectivity and bond graph;
- stiffness and damping;
- tension versus compression behavior;
- diagonal/shear and optional angular or bending bonds;
- fracture thresholds and optional accumulated damage;
- collision surface, binding, and exclusion policy.

In 2D, a triangulated lattice is essential. A rectangular grid with only
horizontal and vertical springs can shear into a rhombus; diagonal bonds make
the mesh carry shear. Under gravity, a cantilever's top bonds can stretch,
bottom bonds can compress, and diagonal bonds can carry shear. Remove material
under an overhang and the changed connectivity redirects load into the
remaining bonds; fracture can emerge without a special "collapse" rule.

This is an intentionally discrete elastic-lattice model. Mesh pattern,
stiffness, timestep, and fracture rules affect its behavior. That sensitivity
is something to expose and investigate, not conceal.

For masonry-like behavior, prefer relatively rigid chunks or coarse strong
interiors joined by weaker brittle mortar bonds. That should read as cracking
and slumping rather than a low-stiffness rubber wall. Later joint diagnostics
may distinguish normal load, shear load, and bending moment, with simple
capacity limits and eventually stress estimates derived from joint geometry.

## Collision Geometry and Topology

The collision surface is related to, but need not be identical with, the
structural graph:

```text
structural graph
  points + bonds + constraints + fracture
        <-> binding / embedding
collision surface
  segments in 2D; triangles in 3D
        <->
render mesh
  material, outlines, cracks, shading
```

At first, collision vertices may simply be structural points. Later a denser
collision or render skin can be embedded in a structural triangle or tetrahedron
with barycentric coordinates. A contact response is distributed back to the
underlying structural points through the same binding.

Triangle surfaces represent concave and holed shapes without treating a whole
body as one convex primitive. They do not remove collision engineering:
broad-phase candidate generation, narrow-phase contact, multiple contacts,
inside/outside behavior, and continuous collision for fast projectiles still
matter. In 2D, the equivalent surface primitive is a segment. A solid 3D body
eventually needs interior tetrahedral structure, not only a deforming triangle
shell.

Self-collision is a graph-and-geometry problem. A point should usually exclude
its incident faces, immediately adjacent topology, and perhaps a small
bond-graph neighborhood, while distant folds and detached components may
collide. Initial scope should exclude self-collision within an intact body and
support only inter-body and ground collision. A fracture can split the bond
graph into connected components, which then become eligible to collide as
independent fragments.

## Constraints and Joints

Persistent constraints are the intentional counterparts to temporary contact
constraints:

- distance constraint or very stiff spring;
- pin joint;
- hinge with optional angular limits;
- fixed/weld joint;
- slider joint;
- transient non-penetration contact with optional friction and restitution.

A pendulum under gravity is the first constraint experiment after the spring
experiments. It is a clear reason to compare force integration with a
constraint solver. Siege toys later use the same vocabulary: a suspended ram,
catapult arm, counterweight, or sling need joints; a wall needs bonds that can
break.

## Renderer and Shader Path

Rendering should begin as an inspector over the same changing mesh that drives
collision, then become a shader-learning path:

1. Flat material rendering and structural/collision overlays.
2. Vertex deformation of the collision/render mesh from particle state.
3. Fragment-shader diagnostic maps: tension, compression, shear, contact,
   constraint error, and impending fracture.
4. Crack seams, texture stretch, fragment outlines, simple lighting, dust, or
   sparks derived from actual simulation events.
5. A higher-detail render skin embedded in the coarse structural material.
6. Only later, GPU compute experiments compared against the known-good CPU
   model.

The CPU model remains authoritative through the learning-focused phases. Its
determinism and traces make it practical to test and review. GPU simulation is
a later experiment because fracture, changing connectivity, and topology-aware
contact are irregular and especially worth understanding first.

## Capstone World: Breach

The project earns its physics abstraction through one small 2D breach game:

- one fixed wall/gatehouse scene;
- a limited set of shots or ram attempts;
- a protected target, opened breach, or collapsed tower as the outcome;
- a replayable trace and explanation of the structural failure;
- no editor, terrain system, material encyclopedia, or 3D requirement.

The player seeks a structural weakness rather than merely hitting a target:
undermine, topple, shear, or punch through. This is complementary to
Barbacane's planning/engineering world without requiring shared code:
Barbacane can reason about a fortification before a siege; this project can
make one small structure fail visibly under a specific applied force.

## Testing Principle

Tests should prove the model and make numerical limits explicit:

- compare constant velocity and gravity with closed-form solutions;
- compare an undamped oscillator with its analytic solution;
- test convergence as timestep decreases;
- record energy drift by integrator and scenario;
- prove deterministic replay for fixed scenarios and inputs;
- assert bond breakage, connected-component changes, and collision eligibility;
- test canonical breach outcomes through both structured diagnostics and a
  headless browser artifact where rendering claims matter.

The browser should support pause, single-step, reset, named scenarios, solver
selection, and overlays. An agent should be able to change a model, run tests,
open a canonical scenario, inspect its diagnostics/screenshot at a fixed tick,
and iterate on the same deterministic evidence.

## Scope Guardrails

- Do not start with an all-purpose physics engine.
- Do not start with a generic entity/component/blackboard game tree.
- Do not start with 3D, self-collision, or a level editor.
- Do not start with historically accurate masonry or siege mechanics.
- Do not move the authoritative simulation to the GPU before the CPU model has
  clear tests and inspectable failure cases.
- Do not promise a game before the one-spring ODE and solver comparison are
  working and explained.

The separate typed game-object-tree idea can later use one small physics
scenario as a proving ground. It should not be a prerequisite for this model:
particles, bonds, and collision faces deserve direct data-oriented
representations while their mathematics is being learned.

## First Runnable Moment

One damped or undamped mass-on-spring scenario runs through explicit Euler,
semi-implicit Euler, and RK4, compares each result against the analytic
solution, and renders the trajectory, energy, and error in a browser with a
headless assertion suite.

## Phase Shape

1. ODE state/derivative contract; analytic reference systems; integrator tests.
2. Browser inspector for named, deterministic one-body scenarios.
3. Coupled springs and a triangulated 2D body.
4. Floor/inter-body contact and a direct visual/contact trace.
5. Bond fracture and a hole/overhang collapse scenario.
6. Pin/hinge constraints and a suspended ram.
7. The one-room breach game, then a v1 postmortem.
8. Decide whether self-collision, catapult/trebuchet, 3D/tetrahedra, a richer
   render skin, or GPU-compute experiments have been earned.

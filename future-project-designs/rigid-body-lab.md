# Rigid Body Lab Design Doc

## Core Question

Can a small, deterministic 2D rigid-body laboratory make translational and
rotational ODEs, collision detection, impulses, contacts, and joints
understandable without attempting to recreate Bullet?

The attractive version is a sequence of explainable physical toys: a circle
bouncing from a floor, an off-centre collision that produces spin, a few boxes
that stack tolerably, and a pendulum or battering ram connected by a joint.
It is a companion to Spring Body Lab, not a replacement for it.

## Shared Foundation

Rigid Body Lab and Spring Body Lab should share a small ODE and math basis:

```text
Vec2, Mat2 / rotation, scalar cross-product helpers
State y
Derivative f(t, y) -> dy/dt
Integrator.step(f, t, y, dt) -> next y
named deterministic scenarios, traces, diagnostics, and analytic references
```

The shared boundary should be intentionally narrow. It owns ordinary math,
state/integrator contracts, test helpers, and scenario/replay conventions. It
does not own a universal `Body`, collision world, entity tree, renderer, or
generic physics framework. Each lab owns its own direct model:

- Spring Body Lab: particles, bonds, deformable material, fracture, and
  collision surfaces.
- Rigid Body Lab: rigid poses, mass/inertia, shapes, contacts, impulses, and
  joints.

The first implementation may live as modules in one learning repository; a
shared library should become a separately published unit only after both labs
have genuinely used the same boundary.

## Mathematical Model

A 2D rigid body has a compact state:

```text
position (x, y)
orientation theta
linear velocity (vx, vy)
angular velocity omega
mass m and moment of inertia I
```

Its continuous motion follows:

```text
dx/dt     = v
dtheta/dt = omega
dv/dt     = F / m
domega/dt = torque / I
```

This is the same ODE-learning spine as the spring lab, now with rotational
motion. A force applied away from the centre of mass creates torque; an
off-centre collision does the same.

Contacts add a discontinuous step after ordinary integration. At a contact
point, each body has a point velocity made from its linear velocity plus its
angular motion. If the contact points are closing, an equal-and-opposite
impulse along the contact normal changes both bodies' linear and angular
velocities. Friction later adds a bounded tangent impulse. The first version
should state every term in its diagnostic rather than hiding it in a solver.

## Scope Ladder

1. A particle/circle under gravity, with no collision.
2. Circle against a static plane, with a visible normal and restitution.
3. Circle versus circle, equal-and-opposite impulse, deterministic replay.
4. Rotation from an off-centre impulse; simple moments of inertia.
5. Convex oriented boxes using the Separating Axis Theorem.
6. Friction and sequential contact impulses; a small, tolerable box stack.
7. One distance or hinge joint; a pendulum and then a suspended battering ram.
8. A postmortem decides whether broad phase, compound shapes, continuous
   collision, sleeping, more joints, or a bridge to breakable walls is earned.

The first runnable moment is deliberately smaller than a physics library: a
circle falls onto a floor, produces a deterministic trace, and the browser
shows its position, velocity, collision normal, and impulse beside headless
tests.

## Collision Scope

V1 starts with circles and static planes. Convex boxes are the first polygon
shape. This avoids the false requirement to solve concave polygons, arbitrary
compound bodies, robust contact manifolds, continuous collision, spatial
acceleration, sleep/island management, or all possible joints before a toy is
alive.

The proper lesson order is:

```text
detect overlap or time of contact
  -> calculate a contact normal and point
  -> calculate relative point velocity
  -> apply an impulse
  -> inspect the changed linear and angular state
```

Sequential impulses are a later, practical approximation for multiple
contacts and stacking. They should be presented as a solver choice whose
iteration count and residual error are inspectable.

## Relationship to the Breach Game

Rigid bodies provide the most direct route from the ODE core to siege toys:

- ram head, catapult arm, and projectile as rigid bodies;
- hinge/distance constraints for the weapon;
- wall chunks and detached rubble as rigid bodies;
- a Spring Body Lab lattice or brittle bonds for a wall that needs distributed
  load and progressive fracture.

The eventual breach game may be hybrid. It should only mix the two models when
each has first earned itself in its own small canonical scenarios.

## Browser and Testing Principle

The browser is an inspector over an authoritative, headless model. It should
pause, step, reset named scenarios, and show centre of mass, orientation,
linear/angular velocity, contact normals, impulse arrows, energy, and solver
residual where relevant.

Tests should include analytic constant-force/constant-torque cases,
deterministic replay, momentum expectations for simple elastic collisions,
non-penetration evidence for canonical contacts, and assertions that an
off-centre impulse changes angular velocity with the expected sign.

## Scope Guardrails

- Do not begin by cloning Bullet or Box2D's API surface.
- Do not begin with a generic game-object or entity framework.
- Do not begin with concave geometry, a level editor, 3D, or a stacking demo.
- Do not make collision response opaque: every canonical contact needs a
  readable calculation trace.
- Do not extract the shared ODE/math basis into a separate package until both
  labs have used it honestly.

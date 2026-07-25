# MoonRock Graphics Lab

## Seed

Recreate the teenage discovery path from BASIC graphics through x86 assembly, mode 13h, keyboard input, and PC-speaker sound as a sequence of tiny runnable experiments.

## Central experience

One DOS graphics screen and one visible machine boundary at a time:

```text
pixel -> line -> sprite -> animation -> keyboard -> speaker -> assembly
```

Each experiment should have a small source file, a reproducible build command, an observable artifact, and a short note explaining the hardware/software boundary it exposes.

## Candidate experiments

- mode 13h palette and pixel plotter
- line and rectangle rasterizer
- keyboard scan-code viewer
- PC-speaker frequency sweep
- page-flipped sprite animation
- wireframe cube with hand-written projection math
- assembly-accelerated inner loop compared with BASIC

## Guardrail

This is a sequence of explanatory toys, not a general DOS game engine. Every new layer must earn itself by making one machine fact visible.


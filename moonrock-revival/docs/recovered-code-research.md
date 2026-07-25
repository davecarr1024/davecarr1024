# Recovered code dump research

Date: 2026-07-25  
Source: `Flyin Hawaiian Productions-20260725T223103Z-1-001.zip`

## Summary

The recovered archive is not a MoonRock source archive. It is a later Flyin' Hawaiian Productions collection containing:

- the compiled Eastman/RPG DOS game and its runtime data,
- a substantial QBasic map-making and RPG asset set,
- the complete source for a rotating-cube QBasic graphics demo,
- several C++/Allegro games and graphics demos,
- a few executables without source.

This is still highly relevant to the MoonRock revival. It shows a clear personal progression from low-level DOS experimentation and QBasic graphics into game construction and then C++/Allegro development. It also gives us a concrete target for the closed Codex loop: make one small graphics artifact runnable and inspectable at each layer.

## What was organized

The archive was preserved untouched and extracted into [`moonrock-revival/`](../). The organized tree is:

```text
moonrock-revival/
  original-dump/                 exact extracted archive contents
  projects/
    eastman/                     QBasic RPG sources/assets and DOS binaries
    qbasic-cube/                 rotating cube source and executable
    cpp-games/                   C++/Allegro projects and demos
    other/tictactoe/             executable-only project
```

The extraction intentionally keeps the original file formats and names where practical. The `original-dump/` tree is a provenance reference; it should not be edited.

## Project inventory

| Recovered project | Language/toolchain evidence | Source status | Research value |
|---|---|---|---|
| Eastman / RPG | QBasic 4.5 expected; DOS `.COM` runtime | Game source missing; map/editor/RPG source recovered | Highest personal and historical value; target for binary preservation and partial reconstruction |
| RPG map editor | QBasic source: `EDITOR.BAS`, `MAP.BAS` | Substantial source recovered | Reveals the data model, tile workflow, map dimensions, and asset conventions |
| Rotating cube | QBasic source: `CUBE.BAS` | Complete source recovered | Best first runnable graphics target; contains homemade 3D projection and rotation math |
| Asteroids | C++ with Allegro | `newasteroids.cpp` recovered | Later evolution of the same graphics/game-making practice |
| Breakout | C++ with Allegro | Source, levels, executable recovered | Complete game loop and content-data example |
| Casino | C++ | Multi-file source and executable recovered | Non-graphics architecture and game-state example |
| Pong | C++ with Allegro | Source and executable recovered | Small interactive loop for toolchain testing |
| Real Sparkler | C++ with Allegro | Source and executable recovered | Small graphics demo for the fast lane |
| Space Invaders | C++ with Allegro | Source, asset, and executable recovered | Larger game-loop and asset example |
| Starfield | C++ | `starfield3d.cpp` recovered | Small 3D/animation stepping stone |
| Tic-Tac-Toe | Unknown from archive alone | Executable only | Low priority until metadata or source is found |

## Eastman: what survives

The outer README says to start Eastman, switch to full-screen mode, and find gameplay instructions in the game. `Eastman.bat` creates `C:\Eastman`, unpacks `zip.zip`, and launches `rpg.com`.

The `zip.zip` payload contains eleven DOS `.COM` files, including `rpg.com`, `HOME.COM`, `PATH1.COM`, `PATH2.COM`, `MIRANDA.COM`, `FINAL.COM`, `RPGPUCK.COM`, `rpgmov.COM`, `NUMBA.COM`, `SHOOT.COM`, and `WINMOV.COM`. These appear to be the game’s compiled rooms/scenes or supporting program pieces, but their exact roles should be confirmed by running them in DOSBox-X and observing the transitions.

The recovered QBasic RPG suite documents the missing game's development tools:

- `EDITOR.BAS` creates textures and assigns physical values: `0` walkable, `1` solid, `2` town.
- `MAP.BAS` places terrain stamps on an 11×7 map and saves `MAIN.MAP` or `TOWN.MAP`.
- `RPG.BAS` loads the maps, draws the background, animates the player sprite, handles arrow-key movement, and applies collision/impact rules.
- `.PIC` files hold packed screen/image data for terrain, coast edges, bridges, the player, and scenery.

The recovered `RPG.BAS` is not the complete Eastman source, but it is a meaningful subsystem: it exposes the map dimensions, 30-pixel tile size, sprite animation strategy, `GET`/`PUT` background restoration technique, and the distinction between visual map stamps and a physical collision map.

## Rotating cube: the strongest recovered artifact

`CUBE.BAS` is a complete, readable QBasic program. It uses `SCREEN 12`, defines typed records for angles, displacement, screen points, and 3D vertices, and renders an eight-vertex cube with `LINE` calls.

The projection is a simple perspective transform:

```text
x' = x / (z + 25)
y' = y / (z + 25)
screen_x = x' * 320 + 320
screen_y = y' * 240 + 240
```

The cube rotates by updating two coordinates at a time around one selected axis. The source uses `ATN` plus quadrant checks to reconstruct a full-angle rotation, then applies `SIN` and `COS`. It contains an optional `dot` routine for experimenting with face centers/ellipses, while the active renderer draws the wireframe edges.

This is exactly the kind of small deterministic world that should anchor the revival. It has visible output, understandable mathematics, no external game assets, and a clean progression:

```text
static cube -> projection -> one-axis rotation -> keyboard camera -> face ordering/shading
```

The existing source also preserves the teenage/early-adult learning path more clearly than a binary can. It is not merely a demo to port; it is a compact record of learning 3D math by making the machine show the result.

## Toolchain eras visible in the dump

There are at least three toolchain eras:

1. **DOS native / low-level era:** Eastman `.COM` programs and QBasic source/assets, with the earlier MoonRock and assembly experiences represented by the history but not by recovered source.
2. **QBasic graphics era:** the cube and RPG tools, expecting QuickBASIC 4.5 or a compatible DOS environment.
3. **C++/Allegro era:** later games and demos with `.cpp`, `.dev`, `.exe`, `alleg40.dll`, score files, levels, and bitmap assets.

The archive therefore supports a revival strategy that respects the original sequence rather than collapsing everything into one modern rewrite.

## Missing or uncertain material

- No MoonRock `.moo` source is present in the dump.
- No original Eastman source is present; only compiled `.COM` components, launcher files, and related QBasic tools/assets survive.
- The exact QuickBASIC 4.5 package is not included. The old README refers to `qb45.zip` from a Geocities page.
- The exact Allegro version and build environment are inferred from `alleg40.dll` and project files, not fully documented.
- Several projects are executable-only or have duplicate archive entries.
- It is not yet known whether the `.PIC` files are directly readable by QBasic `BSAVE`/`BLOAD`, though their sizes and the source strongly suggest a packed QBasic image format.

## Recommended revival sequence

### Phase 1: preserve and understand

- Keep the original archive and extracted `original-dump/` immutable.
- Record hashes for the archive and important binaries.
- Read the QBasic sources and map the relationships among source, `.MAP`, `.PIC`, and `.COM` files.
- Run only in an isolated DOS environment; do not execute unknown binaries directly on the host.

### Phase 2: make the cube visible

- Use QB64-PE or QuickBASIC-compatible tooling to compile/run `CUBE.BAS`.
- Capture a screenshot and, if needed, make a small source-preserving adaptation that exits deterministically after a fixed number of frames.
- Compare the result against the original `CUBE.EXE` in DOSBox-X.

### Phase 3: recover the Eastman experience

- Run `Eastman.bat` and each recovered `.COM` entry point under DOSBox-X.
- Record a room/scene transition map.
- Run `EDITOR.BAS`, `MAP.BAS`, and `RPG.BAS` separately.
- Determine whether the recovered map/texture set can reproduce the original RPG runtime.
- Treat any reconstructed Eastman source as a new, clearly labeled reconstruction, not recovered original source.

### Phase 4: establish the Codex loop

Use a wrapper per lane:

```text
edit source
  -> build
  -> run with fixed input and timeout
  -> capture screenshot / output file / exit code
  -> inspect artifact
  -> make one focused change
```

The first automated target should be the cube because its output can be made deterministic. The first authentic target should be the original `CUBE.EXE`, followed by `RPG.BAS` and the Eastman launcher.

## Research conclusion

The dump gives us a much better endpoint than “find a compiler.” The endpoint is a personal archaeology and revival environment in which the original learning ladder becomes runnable again:

```text
MoonRock/assembly history
  -> QBasic graphics and RPG construction
  -> Eastman’s compiled DOS world
  -> C++/Allegro game-making
  -> Codex-assisted reconstruction and experimentation
```

The rotating cube is the right first artifact: complete source, compact mathematics, immediate visual feedback, and a direct bridge between QBasic, assembly-era graphics thinking, and modern Codex iteration. Eastman should remain the long-term emotional target, but it should be approached after the toolchain and artifact-capture loop are proven on the cube.


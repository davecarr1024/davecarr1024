# MoonRock revival

This directory is an organized working copy of the historical Flyin' Hawaiian Productions code dump from 2025-04-13, preserved in the parent repository as:

`../Flyin Hawaiian Productions-20260725T223103Z-1-001.zip`

The original dump is preserved unchanged under `original-dump/`. The directories under `projects/` are extracted and organized copies intended for inspection and eventual revival. Edit the organized copies, not the archival copy.

## Contents

- `projects/eastman/` — the recovered QBasic map editor, map data, textures, sprites, and RPG runtime assets; the final Eastman/RPG program is present as DOS `.COM` files, but its original source is not present.
- `projects/qbasic-cube/` — `CUBE.BAS`, the source for the rotating-cube demo, plus its compiled `CUBE.EXE`.
- `projects/cpp-games/` — later C++/Allegro games and demos, including source for Asteroids, Breakout, Casino, Pong, Real Sparkler, Space Invaders, and a 3D starfield.
- `projects/other/tictactoe/` — the recovered Tic-Tac-Toe executable.

The inventory and historical interpretation are in [`docs/recovered-code-research.md`](docs/recovered-code-research.md). The broader language/compiler research is in [`../research/moonrock-language-compiler-research.md`](../research/moonrock-language-compiler-research.md).

## Current status

This is an artifact-recovery phase. No compiler or emulator has been installed, and no recovered executable has yet been run on this host. The next useful vertical slice is to run or statically inspect `CUBE.BAS` using a QB64-compatible environment, then establish a DOSBox-X lane for the original DOS binaries and QBasic sources.


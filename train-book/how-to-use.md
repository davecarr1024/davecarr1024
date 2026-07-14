# How To Use The Train Book Docs

Use these docs as a source lens while designing railroad projects.

## If Editing A Project Design

Start with:

1. `cross-reference.md`
2. `project-design-support.md`
3. `themes.md`

Then update the design only with details that become rules, diagnostics, reports, or tests.

## If Building An Automated Analysis

Start with:

1. `topics/book-topics.yaml`
2. `fingerprint.md`
3. `raw/american-railway-1889-ocr.txt`

The raw OCR is noisy. Use it for term scans and source discovery, then confirm important details manually before promoting them into design docs.

## If Creating A New Railroad Project Idea

Answer these questions:

- Which book lens does it isolate?
- What is the fundamental object?
- What period vocabulary should it own?
- What diagnostic/report should be its first artifact?
- Which book details are explicitly out of scope for v1?

Good project mappings:

| Project Shape | Book Lens | First Artifact |
| --- | --- | --- |
| Economy/map analyzer | Way-bills, freight, statistics, civil route burden | Way-bill and route-load report |
| Switching toy | Cars, couplers, brakes, local mechanical handling | Movement and coupling log |
| Interlocking model | Signals, switches, blocks, route authority | Route proof and denial report |
| Locomotive lab | Boiler, valve gear, adhesion, drivers, fuel/water | Mechanical state trace |
| Route-location lab | Survey, grade, curves, bridges, tunnels | Alignment comparison report |

## Promotion Rule

When a book-derived idea gets promoted into a project design, include a short cross-reference back to this directory.

Example:

```text
Book lens: see ../train-book/project-design-support.md, Paper Railroad Support.
```

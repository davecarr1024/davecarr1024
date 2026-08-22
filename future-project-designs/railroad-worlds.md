# Railroad Worlds

This project family is deliberately inspired by *The American Railway: Its Construction, Development, Management, and Appliances*, Dave's "train book." The book is treated as a source lens for period vocabulary, engineering concerns, operating records, and safety logic, not as a demand to build one giant historically complete simulator.

Train-book references now live with the active owner, [Paper Railroad's
research study](https://github.com/davecarr1024/paper_railroad/tree/main/research/train_book):

- [source-text index](https://github.com/davecarr1024/paper_railroad/blob/main/research/train_book/README.md);
- [fingerprint](https://github.com/davecarr1024/paper_railroad/blob/main/research/train_book/fingerprint.md);
- [themes](https://github.com/davecarr1024/paper_railroad/blob/main/research/train_book/themes.md); and
- [cross-reference](https://github.com/davecarr1024/paper_railroad/blob/main/research/train_book/cross-reference.md).
- `train-book-alignment.md`: project-facing analysis of how the book should influence this family.

Rather than one giant railroad simulator, build a family of small projects. Each one isolates a different aspect of railroading and asks:

> What is the smallest executable model that captures why this part of railroading is interesting?

Each project should stand on its own. They should share philosophy, not necessarily code.

## Shared Principles

- Keep each world tiny enough for a v1 to finish in weeks, not years.
- Center each project on one fundamental object.
- Make causality visible: every interesting event should be able to answer why.
- Keep behavior deterministic and replayable.
- Find the right representation before chasing algorithms.
- Build one delightful runnable moment almost immediately.
- Import details from *The American Railway* only when they become executable rules, diagnostics, reports, vocabulary, or tests.
- Let railroad records feel period-correct: way-bill reports, movement logs, route denials, car accounting, and route-load tables are better first artifacts than decorative historical UI.

## Project 1: Paper Railroad

Core question: how does a transportation network create and sustain an economy?

Fantasy: I am the owner of a small railroad. I do not drive trains. I create a transportation network that allows goods to move between industries.

Fundamental object: `Waybill`.

Nothing moves without a waybill. Waybills represent demand, shipment, routing, revenue, and resource consumption. The railroad exists to execute waybills.

Initial scope:

- towns
- industries
- routes
- distances
- producers
- consumers
- goods
- waybills

Do not start with clocks, trains, crews, dispatching, scenery, collisions, or a UI. Start static.

First runnable moment: a map analyzer that explains whether every demand is reachable, whether supply is balanced, which routes are bottlenecks, what transport capacity is required, and whether the railroad can become a going concern.

Growth path:

- v2: operating costs, rates, profitability, empty-car movements
- v3: discrete time and shipments in transit
- v4: trains executing waybills

Detailed design: `paper-railroad.md`.

## Project 2: Janney

Core question: how does switching actually feel?

Fantasy: I am standing beside the train. I do not care about scenery. I care about making and breaking trains.

Fundamental object: `Coupler`.

The coupler is the heart of freight railroading. Everything interesting happens because cars can be assembled into trains, separated, and reassembled somewhere else.

Initial scope:

- one inglenook
- one locomotive
- eight cars
- three sidings
- simple spline track
- no scenery
- no industries
- no economy
- no AI

First runnable moment: pushing cars around is physically satisfying enough that one switching puzzle is fun by itself.

Growth path:

- v2: spline layout editor and save/load
- v3: switching scenarios and scoring
- v4: procedural scenery
- v5: industries, waybills, AI crews

Detailed design: `janney.md`.

## Project 3: Tower

Core question: how do interlockings make railroads safe?

Fantasy: I am standing in the control tower overlooking an interlocking. I do not drive trains or tell engineers how to operate. I establish the constraints under which trains are allowed to move.

Fundamental object: `Route`.

The route is the proof. Every cleared signal represents a demonstrated safe path through the railroad.

Player actions:

- throw switches
- request routes
- clear signals

System responsibilities:

- lock points
- detect occupancy
- enforce conflicting routes
- maintain approach locking
- release routes

First runnable moment: one junction, four switches, six signals, and two trains, with every decision visible and every denied movement explained.

Growth path:

- v2: larger plants and mechanical interlocking
- v3: electric interlocking
- v4: CTC
- v5: multiple towers

Detailed design: `tower.md`.

## Relationship Between Projects

These are not different games. They are different perspectives on the same world.

Paper Railroad asks what should move. It models information, flows, economics, and demand.

Janney asks how it moves. It models physical motion, momentum, couplers, and switching.

Tower asks when it may move. It models authority, signals, interlocking, and safety.

Together they describe a railroad from three independent viewpoints. Each is intentionally small. Each explores one abstraction. Each tries to make an invisible system visible.

For a comparison against the developer-record design and execution goals, see `railroad-fit-analysis.md`. For the book-derived source lens, see the [Paper Railroad cross-reference](https://github.com/davecarr1024/paper_railroad/blob/main/research/train_book/cross-reference.md) and `train-book-alignment.md`.

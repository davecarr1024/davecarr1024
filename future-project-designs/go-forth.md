# Go Forth Design Doc

## Core Question

Can a railway planner start with a traveler's current state and desired kind of
day, then reveal interesting one-way possibilities, instead of requiring a
destination before it can plan anything?

**Go Forth** is an open-ended Japan railway adventure planner. Conventional
journey tools answer:

> I am at A. I need to get to B. What is the fastest practical route?

Go Forth answers:

> I am here. I have the rest of the day. What interesting things could I do
> with the railway?

It is a destination-discovery and adventure-planning tool, not a real-time
timetable, ticketing system, or navigation replacement.

## Fantasy

I wake up in Kanazawa with one backpack, no appointment beyond eventually
finding a comfortable hotel, and permission to choose the day according to
energy, weather, curiosity, or whim.

I can say:

- I want to be on trains most of today.
- I want to move generally south, but I do not care how far.
- I am tired: no more than one transfer and an easy station hotel tonight.
- I want an interesting place from my guidebook, then I want to continue from
  there rather than backtrack.
- I feel like splurging on GranClass if it fits naturally.
- I have no idea. Give me something weird.

The planner expands outward from where I am and offers a small collection of
qualitatively different adventures. A train journey can be the day's activity;
a destination can simply become tomorrow's starting point.

## Fundamental Shape

The central object is a **reachable adventure**: an explainable, scored path
from the user's current state to a plausible next overnight or reassessment
point.

The underlying model is a time-dependent weighted railway graph:

- nodes are stations and optional tourist stops;
- edges are typical service-pattern movements, not individual departures;
- paths accumulate practical costs and experiential bonuses;
- endpoint annotations explain what makes an arrival useful or interesting.

The UI should make the possibility space visible before it makes a route look
optimal.

```text
YOU ARE HERE
Kanazawa · 09:14

├─ Toyama     quick hop · frequent · Green available
├─ Tsuruga    easy southward move · station interest
├─ Tokyo      long comfortable ride · huge onward possibility space
├─ Nagano     moderate ride · easy overnight
└─ Go farther...
```

Selecting a possibility expands the graph from that new state. A map can help,
but the heart of the product is: **show me where I could go from here.**

## Product Principles

### Adventure planning, not departure information

The baked dataset need not be exact or real time. It can represent typical
travel times, broad service patterns, approximate frequencies, service class,
and useful annotations. The interface must say plainly:

> Adventure planning, not departure information. Check current railway
> information before boarding.

Being wrong by five minutes is unimportant. Knowing that a route is frequent,
sparse, comfortable, scenic, or likely to be a useful move is valuable.

### Approximation is a feature

Exact departures bring data, licensing, and freshness complexity that the core
experience does not require. Routing can use expected wait rather than a
specific train:

```text
estimated traversal cost = typical running time
                         + expected wait
                         + transfer cost
```

Sparse services should be represented honestly with a confidence level and an
explicit warning to verify the live timetable before committing.

### Comfort is an edge weight

Ordinary cars are valid. Green Car is a planning bonus, not a requirement;
GranClass is an optional splurge. A useful ordinary-seat route can beat a
slower or stranger route that happens to have a premium car.

### One-way tourism is normal

The project rejects the default assumption that every attraction is a day trip
from a base hotel. An attraction can be a node in a continuing journey:

```text
hotel → railway → attraction → reassess → somewhere else → sleep
```

The endpoint is allowed to be arbitrary. Ending in Hakodate, Akita, Hamamatsu,
or Kagoshima because the enjoyable railway day led there is a success.

### Preferences should beat constraints

Hard constraints should be rare: latest arrival, maximum transfers,
accessibility needs, an operator to avoid, or a region that must be reached.
Most qualities are preferences: scenery, novelty, direction, long rides,
Green/GranClass availability, endpoint convenience, and railfan value. This
keeps the system from returning "no route" when the ideal is unavailable.

## Planning Modes

Modes are preset weights over one graph, rather than separate planners.

| Mode | Emphasis |
| --- | --- |
| Normal | Balanced time, comfort, interest, and robustness. |
| Quiet | Few transfers, frequent service, easy endpoints. |
| Train Day | Long, comfortable, scenic rides are desirable. |
| Progress | Movement toward a broad direction or region. |
| Tourist | Incorporate an attraction, then leave the endpoint open. |
| Weather Escape | Movement toward better weather; a later external input. |
| GranClass | Strong preference for opportunities without making the route absurd. |
| Goblin | Unusual feasible services, odd loops, and surprising endpoints. |

Example queries include:

- “I'm in Kanazawa at 09:00. Show me interesting places I could plausibly end tonight.”
- “I want to leave now and spend two or three hours comfortably on a train.”
- “Move me generally toward Kyushu today, but I don't care how far.”
- “Maximize enjoyable railway time. Keep transfers reasonable and get me to an easy hotel by 21:00.”
- “Where could I incorporate GranClass today without making the route absurd?”

## Scoring Model

A route combines conventional cost with experience. A rough utility shape is:

```text
utility(path) =
    - travel_time
    - transfer_penalty
    - expected_wait
    - fragile_connection_penalty
    - sparse_service_penalty

    + comfort_bonus
    + scenery_bonus
    + interesting_train_bonus
    + novelty_bonus
    + destination_bonus
```

Mode-specific weights change the result. Low-energy days make transfers and
fragile connections expensive. Train Day can treat travel time as positive
within a desired range. Progress rewards movement toward a broad region without
requiring a final city. Goblin Mode increases the weight or selection chance of
unusual but plausible paths.

The result should be five to ten diverse possibilities, not fifty nearly
identical shortest paths. Every result should explain why it appeared.

## Data Model

V1 does not need every station or every departure in Japan. The useful backbone
can begin with the Shinkansen, major JR hubs, important limited expresses,
selected conventional trunk routes, and a growing set of interesting private
railways and branches.

The frozen, versioned network can live in JSON, SQLite, DuckDB, or a similarly
simple indexed format, for example `network-2026-09`.

Useful station fields include:

```text
station_id, name_ja, name_en, latitude, longitude, operators, major_hub,
hotel_convenience, food_convenience, tourist_interest, good_day_endpoint, notes
```

Service patterns, rather than individual trains, include:

```text
service_id, operator, service_name, service_class, from_station, to_station,
typical_runtime, approx_frequency, service_window, reserved_only,
ordinary_available, green_available, granclass_available, jr_pass_status,
supplement_notes, rolling_stock, scenic_score, railfan_interest,
reliability_notes
```

The differentiator is a subjective human annotation layer:

```text
scenic_score, train_nerd_score, comfort_score, interesting_station_score,
station_hotel_score, ekiben_score, good_for_long_ride, good_for_rainy_day,
good_for_low_energy, good_for_spontaneous_overnight,
worth_riding_for_no_particular_reason
```

Subjectivity is a feature here; it is precisely what conventional route planners
do not model.

## Dataset Strategy and Provenance

Potential build inputs include appropriately licensed open GTFS / GTFS-JP data,
ODPT data, published route information where reuse is permitted, station
coordinates, and manually maintained service-pattern and experiential data.

The runtime must use a baked release rather than depend on external sources.
The build pipeline preserves source and licensing metadata for each imported
component:

```text
source datasets → normalizers → service-pattern builder → manual annotations
                → validation → network-YYYY-MM → Go Forth
```

Data acquisition is an independent engineering concern, not the first product
deliverable.

## Non-Goals

V1 does not need:

- live departures, delays, platforms, disruption handling, or seat inventory;
- ticket or hotel purchasing;
- exact walking directions;
- perfect national coverage;
- guaranteed feasibility for sparse or unusual services; or
- an operational replacement for official railway tools.

Go Forth offers an interesting, well-explained idea. Official railway
information gets the traveler onto the train.

## V1 Thesis

The smallest worthwhile v1 is a planner over roughly 100–300 strategically
useful stations.

Given an origin, start time, latest arrival, maximum transfers, and a mode or
preference profile, it returns five to ten diverse reachable adventures with
confidence and explanation.

The first interface asks:

> Where are you?

Then:

> What kind of day sounds good?

And offers cards such as:

- **Easy** — a comfortable two-hour ride ending at a useful city.
- **Interesting** — a railway or destination with a particular appeal.
- **Far** — a long train day that dramatically changes tomorrow's starting point.
- **Weird** — a plausible choice a conventional planner would not suggest.

## First Runnable Moment

The first delightful moment is not a nationwide website. It is a small command
or local page that starts from Kanazawa and produces several meaningfully
different, explainable railway days:

```text
Go Forth · Kanazawa · 09:00 · Train Day

Easy: Tsuruga
  1h 05m typical travel · frequent · easy southward move

Comfortable: Tokyo
  2h 35m typical travel · Green available · huge onward possibility space

Interesting: Nagano
  1h 50m typical travel · moderate ride · easy overnight

Weird: Go farther through an annotated branch
  Plausible, but sparse service: verify today's timetable before committing
```

If that result feels like the railway has become a possibility engine, the
project has earned its next layer.

## Growth Path

1. **Curated backbone:** a small baked Japanese network with clear sources and
   hand-authored endpoint annotations.
2. **Diverse routing:** weighted paths, transfer/wait penalties, confidence,
   and explanation.
3. **Reachability UI:** expansion from the current state and saved adventure
   possibilities.
4. **Annotation depth:** scenic, railway, food, station-hotel, and low-energy
   knowledge earned route by route.
5. **Optional live helpers:** weather input or handoff links only if they
   preserve the offline, approximate planning thesis.

## Project Thesis

Japan's railway network is not only a mechanism for connecting planned
destinations. For a flexible traveler, it is a **possibility engine**.

**Don't tell me how to get where I've already decided to go. Show me where I
could go from here.**


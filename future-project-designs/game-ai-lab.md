# Game AI Lab Design Doc

Status: promoted to `~/projects/game_ai_lab` and completed as a v1 research
proof. This file is retained as the origin design. The project README, status
narrative, technical description, and retrospective are authoritative for its
implemented capabilities and findings.

## Core Question

Can an abstract board-game representation capture enough of a game's state, move space, reward structure, and terminal conditions that one AI system can play many different games effectively through the same interface?

This revisits the GBGE / ESS idea, but with a sharper constraint: the abstraction must be earned by concrete games and measured by actual play.

The question is not "can I design a perfect generic board-game engine?" The question is whether there is a small, useful interface through which different games can expose:

- legal state,
- legal moves,
- state transitions,
- rewards or outcomes,
- terminal conditions,
- hidden or public information,
- evaluation signals,
- explanations for moves.

Then an AI can reason through that interface without being custom-built for each game.

## Fantasy

I define Tic-Tac-Toe, Connect Four, Othello, or a small custom game in a compact game model.

The same AI can ask:

- What state am I in?
- What moves are legal?
- What happens if I make this move?
- Did the game end?
- What reward did I receive?
- What future states are reachable?
- Why did I choose this move?

Then it can play competently through search, rollout, evaluation, or learning strategies.

The delightful moment is watching the same AI code play two different games because the games expose the right concepts.

## Fundamental Object

`GameState`.

The game state is the truth of the world at one moment. Everything else derives from it:

- legal moves,
- next states,
- terminal outcome,
- reward,
- evaluation,
- explanation,
- training sample,
- search node.

The AI should not know the concrete game's board internals unless it is using an explicitly game-specific evaluator. The common interface should be real enough that generic algorithms can operate on it.

## Why This Fits

This idea connects directly to older repos:

- `ess`: board trees, min-max, board evaluators, players.
- `esh`: C# board-game representation.
- `gbge`: generic board-game engine abstraction.
- `banana` and `sudoku`: search spaces, constraints, propagation, and strategy comparison.

It also revisits a known caution: a generic engine is less satisfying than one complete game whose rules can be explained.

The way to make this fit is to invert the old risk. Do not start by designing an all-purpose game engine. Start with one or two concrete games, then extract the smallest interface that lets one AI play both.

## Non-Goals

- Do not start with every kind of board game.
- Do not start with hidden information games.
- Do not start with stochastic games.
- Do not start with multiplayer beyond two-player zero-sum.
- Do not start with neural networks.
- Do not start with reinforcement learning infrastructure.
- Do not start with a GUI.
- Do not build a generic engine before concrete games exist.

V1 should not handle poker, Catan, D&D, simultaneous turns, negotiation, incomplete information, or arbitrary reward systems.

## V1 Thesis

The smallest worthwhile v1 is one generic search AI playing two small deterministic perfect-information games through the same interface.

Good v1 game candidates:

- Tic-Tac-Toe plus Connect Four mini-board,
- Tic-Tac-Toe plus Othello mini-board,
- Connect Four mini-board plus a simple custom territory game.

V1 should support:

- deterministic two-player turns,
- full public state,
- legal move enumeration,
- pure state transition,
- terminal outcome,
- simple reward,
- minimax or alpha-beta AI,
- random baseline player,
- game-specific optional evaluator,
- match runner,
- move explanation.

## Model Objects

- `GameState`: immutable snapshot of game state.
- `Move`: legal action from a state.
- `Player`: active side or agent identity.
- `GameRules`: interface for legal moves, transition, terminal checks, and rewards.
- `Outcome`: win/loss/draw or numeric reward.
- `SearchNode`: state plus move, depth, score, and children.
- `Policy`: AI strategy that chooses a move.
- `Evaluator`: optional heuristic for non-terminal states.
- `Match`: sequence of states and moves.
- `MoveExplanation`: why a policy chose a move.
- `GameSpec`: concrete game's rules, initial state, display helpers, and tests.

## First Questions

- What is the smallest interface that can represent two games honestly?
- Can the rules be pure and deterministic?
- Can the same minimax implementation play both games?
- Can an AI explain a move in terms of search results?
- Can a game-specific evaluator plug in without contaminating the generic AI?
- Can matches be replayed deterministically?
- Can tests assert rules, transitions, terminal states, and AI choices?

## First Runnable Moment

The first delightful runnable moment is a match report:

```text
Game: Tic-Tac-Toe
AI: AlphaBeta(depth=9)
Opponent: Random(seed=4)

Move 1: X -> center
Reason:
  score: draw-or-better
  searched states: 1243
  best replies considered: 4

Result: X wins in 7 moves

Game: Mini Connect Four
AI: AlphaBeta(depth=6)
Opponent: Random(seed=4)

Result: AI wins in 12 moves
Same policy implementation: yes
```

The goal is not a beautiful UI. The goal is proving that the abstraction is strong enough for one policy to play multiple games.

## Representation Principle

Concrete games come first, but generic contracts must be explicit.

A good game interface should probably require:

- `initial_state()`,
- `current_player(state)`,
- `legal_moves(state)`,
- `apply_move(state, move) -> state`,
- `is_terminal(state)`,
- `outcome(state)`,
- `reward(state, player)`,
- optional `display(state)`,
- optional `explain_move(state, move)`.

State transitions should be pure. If a game cannot be tested through state snapshots and moves, the abstraction is already too vague.

## Testing Principle

The proof suite should test both concrete games and generic AI.

Concrete game tests:

- legal moves from initial state,
- illegal move rejection,
- state transition correctness,
- terminal state detection,
- outcome/reward correctness,
- replay determinism.

Generic AI tests:

- minimax finds forced wins in simple positions,
- alpha-beta returns the same move as minimax,
- random policy is deterministic with a seed,
- evaluator affects move choice only when search depth is limited,
- match runner records every state and move,
- move explanations cite search scores and candidate moves.

The abstraction is only real when the same AI tests run across more than one game.

## V1 Scope

V1 includes:

- two deterministic perfect-information games,
- immutable state models,
- legal move enumeration,
- pure transitions,
- terminal outcome and reward,
- random policy,
- minimax or alpha-beta policy,
- optional game-specific evaluator,
- match runner,
- replayable match log,
- text display,
- move explanation,
- tests for rules and AI behavior.

V1 excludes:

- GUI,
- multiplayer beyond two-player games,
- hidden information,
- stochastic transitions,
- simultaneous turns,
- neural networks,
- reinforcement learning,
- Monte Carlo Tree Search unless minimax/alpha-beta is already stable,
- generic plugin/package system.

## Growth Path

### Layer 1: One Concrete Game

Implement Tic-Tac-Toe end to end: rules, state, moves, match runner, random player, tests.

### Layer 2: One AI

Implement minimax or alpha-beta against Tic-Tac-Toe with move explanations.

### Layer 3: Second Game

Add a second concrete game and force the interface to become honest. Change the abstraction only when the second game proves the need.

### Layer 4: Evaluation And Benchmarking

Add game-specific evaluators, match tournaments, score summaries, and strategy comparison.

### Layer 5: Broader Game Classes

Consider MCTS, stochastic games, hidden information, or learning only after deterministic perfect-information games are stable.

## Fit Analysis

### Fit Score

Game AI Lab is a strong idea with a known abstraction risk.

| Goal | Fit | Notes |
| --- | --- | --- |
| Small deterministic world | Strong if scoped | Two small deterministic games are manageable. |
| One fundamental object | Strong | `GameState` anchors rules, moves, rewards, and search. |
| Causality and explanation | Strong | Search trees and move explanations can show why a move was chosen. |
| Tests as proof | Strong | Rules, transitions, terminal states, and AI choices are naturally testable. |
| Start delightfully small | Strong | Tic-Tac-Toe plus minimax can work quickly. |
| Avoid generic-engine trap | Medium to weak | This is the main danger; concrete games must come first. |
| Personal hook | Strong | It revives GBGE/ESS with clearer standards and agent-driven discipline. |
| Execution risk | Medium | Algorithms are known; abstraction design is the risk. |

### Why It Might Be Worth Building

This is a clean way to explore "what is a game?" in executable form.

It also creates a satisfying testbed for AI reasoning that does not require neural networks or huge infrastructure. A generic minimax or alpha-beta player that can move from Tic-Tac-Toe to another game through a shared interface would be a real proof of concept.

### Main Risks

- Designing the universal interface before the second game exists.
- Spending too much time on engine architecture.
- Building a framework instead of a game-and-AI laboratory.
- Choosing games that are too different too early.
- Letting AI ambition jump to RL/neural systems before search and evaluation are understood.

### Scope Guardrails

- V1 must include at least one complete concrete game before abstraction work.
- V1 must include exactly two games before claiming the interface is generic.
- V1 must use deterministic perfect-information games.
- V1 must include one generic AI policy that works for both games.
- V1 must produce match logs and move explanations.
- V1 must not include GUI, hidden information, stochasticity, or neural networks.

### Recommended Execution Plan

1. Write `README.md` and `docs/design.md` with the exact two V1 games named.
2. Implement Tic-Tac-Toe rules, state, moves, terminal checks, and tests.
3. Implement random policy and match runner.
4. Implement minimax or alpha-beta with explanations.
5. Add a second small deterministic game.
6. Refactor only the interface needed by both games.
7. Add cross-game policy tests.
8. Add benchmark/tournament output.
9. Write a v1 postmortem before adding more game types or AI methods.

## Relationship To Existing Projects

- `GBGE`: original generic board-game engine idea.
- `ESS` / `ESH`: board, min-max, evaluator, and player experiments.
- `Sudoku` / `Banana`: search spaces and solver strategy comparison.
- `Project Philosophy`: direct caution that generic engines need a concrete experience first.

Game AI Lab should proceed only if its thesis is "earn a small game interface by making one AI play two real games," not "design the universal game engine up front."

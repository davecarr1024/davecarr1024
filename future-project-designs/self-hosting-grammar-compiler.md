# Self-Hosting Grammar Compiler Concept

## Purpose

This document explores a possible future direction after Rule Lab:

> A self-hosting grammar compiler that parses textual grammar descriptions,
> analyzes them, builds an executable parser, and emits a language-neutral
> syntax tree for downstream tools.

The parser is responsible for syntax.

The interpreter, compiler, analyzer, language server, or other downstream
consumer remains a separate system.

The central pipeline is:

```text
grammar source
  -> grammar parser
  -> grammar AST
  -> grammar analysis
  -> parser machine
  -> source parser
  -> generic syntax tree
  -> downstream system
```

This direction replaces recursive executable parser references with a finite
descriptive grammar model. Recursion exists symbolically in grammar productions
rather than through linked runtime rule objects.

## Core Idea

Instead of defining a recursive grammar as a graph of executable C++ rules:

```text
Rule<State, Expr>
  -> Ref<State, Expr>
```

the user writes a textual grammar:

```text
grammar Calculator;

token INTEGER = /[0-9]+/;
token PLUS = "+";

Expr
  : Expr PLUS Term
      => (Add :left $1 :right $3)
  | Term
      => $1
  ;

Term
  : INTEGER
      => (Integer :value $1)
  ;
```

The grammar compiler parses this description into a grammar AST, resolves
symbolic references, performs formal grammar analysis, constructs a parsing
machine, and uses that machine to parse source programs.

The generated parser emits a generic structured syntax tree rather than
requiring direct construction of C++ domain objects.

## Architectural Separation

The system is divided into distinct modules.

### Grammar Frontend

The grammar frontend owns:

- parsing grammar-description files,
- grammar syntax diagnostics,
- token and production declarations,
- emit-expression parsing,
- source locations,
- construction of `GrammarAst`.

### Grammar Compiler

The grammar compiler owns:

- symbol resolution,
- duplicate and missing symbol diagnostics,
- start-symbol selection,
- reachability analysis,
- nullable analysis,
- FIRST and FOLLOW sets where applicable,
- LR-family item construction,
- closure and goto computation,
- conflict detection,
- parser-table construction,
- parser-machine validation.

### Parser Runtime

The parser runtime owns:

- token consumption,
- parser state and semantic stacks,
- shift, reduce, accept, and error actions,
- reduction capture collection,
- emit-expression evaluation,
- construction of generic syntax values,
- structured parse diagnostics.

### Downstream System

The downstream system owns:

- name resolution in the parsed language,
- type checking,
- semantic validation,
- lowering,
- optimization,
- interpretation,
- code generation,
- execution.

The parser must not silently absorb compiler responsibilities merely because it
can construct C++ objects.

## Language-Neutral Parser Output

The parser output should be a generic syntax representation.

Conceptually:

```cpp
struct SyntaxNode {
  std::string kind;
  SourceSpan span;
  std::map<std::string, SyntaxValue> fields;
};
```

A syntax value may contain:

```cpp
using SyntaxValue = std::variant<
    std::monostate,
    bool,
    std::int64_t,
    double,
    std::string,
    SyntaxNode,
    std::vector<SyntaxValue>>;
```

The internal representation should not be defined as JSON, but JSON should be a
natural serialization.

Other possible encodings include:

- CBOR,
- MessagePack,
- protobuf,
- Cap'n Proto,
- a compact Rule Lab binary format.

This allows the parser to sit behind a process or module boundary.

Possible consumers include:

- a C++ compiler,
- a Python analysis tool,
- a JavaScript visualizer,
- a language server,
- a test harness,
- a remote compilation service.

The correct representation depends on what is downstream.

## Syntax Tree Versus Parse Tree

The parser should not necessarily emit a raw parse tree.

A parse tree mirrors grammar productions:

```text
expression
  expression
    term
      integer
  PLUS
  term
    integer
```

A syntax tree represents semantic syntax:

```text
Add
  left: Integer(1)
  right: Integer(2)
```

Grammar productions therefore need a declarative tree-shaping mechanism.

## Emit Expressions

Each production may include an emit expression describing how captured
production values become syntax output.

Example:

```text
Expr
  : Expr PLUS Term
      => (Add :left $1 :right $3)
```

The right-hand side provides positional captures:

```text
$1 = first production value
$2 = second production value
$3 = third production value
```

The emit expression reshapes those captures into a structured syntax value.

This is intentionally similar to regex capture replacement:

```text
pattern captures
  -> replacement template
```

The difference is that captures are parser values and replacements build trees
rather than strings.

Conceptual operations include:

```text
$1
```

Return a captured value directly.

```text
(Add :left $1 :right $3)
```

Construct a syntax node.

```text
(list $1 $3)
```

Construct a list.

```text
(flatten $1)
```

Flatten a repeated capture.

```text
(optional $4)
```

Represent optional syntax.

```text
(span $1 $3)
```

Construct or merge source-span information.

```text
(null)
```

Emit no semantic value.

## Lisp-Shaped Emit Language

The emit-expression language naturally wants an s-expression syntax.

Example:

```lisp
(Add
  :left $1
  :right $3
  :span (merge-span $1 $3))
```

This shape is attractive because it provides:

- trivial parsing,
- no operator precedence,
- uniform structure,
- natural nesting,
- simple interpretation,
- straightforward serialization,
- direct correspondence between syntax and syntax trees.

The language should initially remain a constrained tree-construction algebra
rather than a general-purpose Lisp.

A possible initial grammar is:

```text
emit-expression :=
    capture
  | literal
  | constructor
  | list-expression
  | optional-expression
  | span-expression
  | pure built-in transform
```

Example constructors:

```lisp
(Integer :value $1)

(Call
  :callee $1
  :arguments (flatten $3))

(If
  :condition $2
  :then $4
  :else (optional $6))
```

## Avoiding Arbitrary Embedded Code

The first design should not allow arbitrary C++ or arbitrary Lisp inside
grammar files.

Arbitrary embedded code would:

- make grammar analysis incomplete,
- couple grammars to one host language,
- weaken portability,
- complicate sandboxing,
- make generated artifacts harder to inspect,
- blur the parser/compiler boundary.

Emit expressions should remain:

- pure,
- deterministic,
- structurally analyzable,
- side-effect free,
- limited to syntax construction and normalization.

A richer transformation language may later earn its place, but it should not
arrive accidentally through convenience features.

## Parser Formalism

The initial parser compiler should likely target canonical LR(1).

Canonical LR(1) offers:

- explicit lookahead,
- conceptually direct item construction,
- clearer conflict explanations,
- no conflict changes caused by state merging,
- a strong reference model for later optimizations.

LALR may later be added as a table-compression backend.

The compiler pipeline is:

```text
GrammarAst
  -> ResolvedGrammar
  -> NormalizedGrammar
  -> LR(1) items
  -> closure and goto
  -> canonical item sets
  -> ACTION and GOTO tables
  -> CompiledGrammar
```

A future LALR backend may merge compatible LR(1) states and report:

- which states were merged,
- which lookaheads were combined,
- whether merging introduced new conflicts,
- table-size differences.

## Runtime Parser Machine

The first execution engine may be entirely runtime-driven.

Conceptually:

```cpp
struct CompiledGrammar {
  std::vector<ParserState> states;
  std::vector<Action> actions;
  std::vector<Goto> gotos;
  std::vector<Production> productions;
};
```

The parser machine maintains:

```text
state stack
semantic-value stack
source-span stack
input token cursor
```

Possible actions are:

```text
Shift(next_state)
Reduce(production)
Accept
Error
```

On reduction:

1. Pop the production's right-hand-side states and values.
2. Expose those values as captures.
3. Evaluate the production's emit expression.
4. Push the resulting syntax value.
5. Follow the corresponding goto transition.

The runtime implementation should be inspectable and serve as the reference
model for any generated or compile-time backend.

## Optional C++ Source Emission

C++ source generation may be added as a backend, but it is not required for the
parser to have value.

A C++ backend could emit:

- token enums,
- parser-state tables,
- production metadata,
- reduction dispatch,
- emit-expression bytecode or generated constructors,
- source-span handling,
- diagnostics,
- a typed or generic parse entry point.

Possible generated interface:

```cpp
std::expected<SyntaxNode, ParseError>
parse(std::string_view source);
```

However, generated C++ is an optimization and integration choice.

The core product remains:

```text
grammar description
  -> compiled parser artifact
```

That artifact may be:

- an in-memory runtime object,
- a serialized parser package,
- generated C++,
- generated Rust or another language,
- a remotely hosted parsing service.

## Bootstrap Strategy

The system can become self-hosting incrementally.

### Stage 0: Bootstrap Parser

Use the existing Rule Lab parser combinators or a tiny handwritten parser to
parse the first grammar-description language.

This produces `GrammarAst`.

### Stage 1: Runtime Grammar Compiler

Implement:

- grammar resolution,
- grammar validation,
- canonical LR(1) construction,
- parse-table generation,
- runtime parser execution,
- generic syntax-tree emission.

At this stage, the grammar parser remains handwritten or combinator-based.

### Stage 2: Describe The Grammar Language

Write the grammar-description language in its own syntax:

```text
rule_lab_grammar.rl
```

Use the bootstrap parser and grammar compiler to compile this file into a
parser for Rule Lab grammar files.

### Stage 3: Parser Parity

Run both parsers over the same grammar corpus:

```text
bootstrap parser
generated grammar parser
```

Compare:

- grammar ASTs,
- normalized grammar IR,
- diagnostics,
- source spans,
- generated parser tables.

### Stage 4: Self-Hosting

Use the generated grammar parser to parse `rule_lab_grammar.rl`.

Compile the resulting grammar again.

The system reaches a fixed point when repeated generations produce equivalent
normalized output:

```text
generation 1
  -> generation 2
  -> generation 3
```

Expected invariant:

```text
normalize(generation N)
  == normalize(generation N + 1)
```

The bootstrap parser remains as:

- a seed,
- a parity oracle,
- a recovery tool,
- historical proof code.

## Self-Hosting Emit Language

The emit-expression language may itself be described in the grammar language.

Because emit expressions use a Lisp-shaped syntax, their parser should be
small:

```text
EmitExpr
  : CAPTURE
  | STRING
  | NUMBER
  | LPAREN SYMBOL EmitArgs RPAREN
  ;
```

The grammar parser therefore emits a `GrammarAst` containing emit-expression
ASTs.

The parser compiler stores or compiles those emit expressions.

The runtime parser later evaluates them to construct syntax trees.

This creates the self-hosting loop:

```text
grammar parser
  parses grammar source
  containing emit programs
  -> GrammarAst

grammar compiler
  compiles productions and emit programs
  -> CompiledGrammar

compiled grammar parser
  parses source
  -> syntax tree
```

Eventually, the grammar describing emit expressions is itself compiled by the
same system.

## Relationship To Rule Lab

This direction does not invalidate the Rule Lab work.

The existing work provides:

- lexer machinery,
- source spans,
- structured diagnostics,
- typed state transition concepts,
- syntax combinators,
- a bootstrap parser,
- property-analysis ideas,
- experience distinguishing structural and semantic identity.

The main architectural shift is narrower:

```text
recursive executable parser graph
  -> descriptive grammar compiled into a parser machine
```

The generic rule model may still describe compiler passes:

```text
Rule<TextState, GrammarAst>
Rule<ResolutionState, ResolvedGrammar>
Rule<AutomatonState, ParseTables>
Rule<ParserState, SyntaxNode>
```

Rule Lab becomes a broader laboratory for inspectable transformations rather
than only a parser-combinator library.

## Relationship To Phase 15

Phase 15 exposes the limits of recursive executable rule graphs.

Its concepts map naturally into the descriptive compiler model:

```text
canonical bindings
  -> nonterminal declarations

Ref<State, T>
  -> symbolic production references

finalization
  -> grammar resolution and linking

property sidecars
  -> grammar analyses

composed root rule
  -> grammar start symbol and owned production set
```

The Phase 15 implementation remains useful as:

- a proof of the original model,
- the likely bootstrap parser mechanism,
- evidence motivating descriptive grammar compilation,
- a source of reusable traversal and diagnostic ideas.

## Initial Grammar Language Sketch

A deliberately small first language might support:

```text
grammar Calculator;

skip WHITESPACE = /[ \t\r\n]+/;

token INTEGER = /[0-9]+/;
token PLUS = "+";
token LPAREN = "(";
token RPAREN = ")";

start Expr;

Expr
  : Expr PLUS Term
      => (Add :left $1 :right $3)
  | Term
      => $1
  ;

Term
  : INTEGER
      => (Integer :text $1)
  | LPAREN Expr RPAREN
      => $2
  ;
```

Initial features:

- named literal and regex tokens,
- skipped lexer rules,
- named nonterminals,
- one start symbol,
- production alternatives,
- positional captures,
- s-expression emit forms,
- generic syntax-tree output,
- source-span preservation,
- canonical LR(1) compilation.

Initial non-features:

- arbitrary embedded code,
- macros,
- grammar inheritance,
- precedence declarations,
- error-recovery productions,
- multiple parser backends,
- generalized parsing,
- typed host-language semantic actions.

Those features may be explored only after the complete bootstrap loop works.

## First Proof Milestones

1. Define `GrammarAst`.
2. Define the textual grammar subset.
3. Parse it with the existing parser stack.
4. Resolve token and nonterminal symbols.
5. Normalize productions.
6. Compute canonical LR(1) item sets.
7. Build ACTION and GOTO tables.
8. Detect and explain conflicts.
9. Execute the tables against a token stream.
10. Implement positional production captures.
11. Parse and evaluate constrained emit expressions.
12. Emit a generic syntax tree.
13. Serialize syntax output as JSON.
14. Describe the grammar language in itself.
15. Prove bootstrap/generated-parser parity.
16. Prove stable self-generation.

## Non-Goals

The first implementation should not:

- become a production replacement for yacc or Bison,
- parse arbitrary C++ semantic actions,
- implement a full Lisp,
- build a complete compiler toolchain,
- optimize parser-table size prematurely,
- support every grammar formalism,
- hide parser states and conflicts behind opaque APIs,
- require generated C++ to prove value,
- merge parsing and downstream semantic compilation.

## Canonical Principle

**Describe syntax as data. Parse the description. Analyze it. Compile it into a
machine. Let that machine emit structured syntax for whatever system comes
next.**

The parser parses grammars.

The grammar compiler builds parsers.

The emit language builds trees.

Eventually, the whole arrangement describes and rebuilds itself.

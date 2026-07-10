# Compiler Lab Design Doc

## Core Question

Can I learn the basics of compiler design by building a small language pipeline that produces inspectable intermediate forms and runs real test programs in a simple machine-code environment?

The seed is not "invent a production language." The seed is a learning laboratory: source text goes through lexing, parsing, semantic analysis, three-address code, lowering, machine code or bytecode, and execution. Each stage should be visible, testable, and understandable.

The goal is to learn compiler fundamentals deliberately. I have picked up pieces of compiler design by accident through IRATA, Pysh, parsers, assemblers, and interpreters, but I never took a compilers course. This project should treat the standard language and patterns of compilers as the subject: lexical analysis, grammars, parsing, ASTs, semantic analysis, IR, control flow, lowering, calling conventions, object formats, and execution.

## Fantasy

I write a tiny program in a tiny language.

I can see:

- the tokens,
- the parse tree,
- the typed AST,
- the three-address code,
- the lowered instruction stream,
- the machine or VM state while it runs,
- the final output.

Every stage is a building block. Every stage has tests. Every stage can be inspected when something is wrong.

It should also feel a little historical. I want to understand why standard intermediate representations and simple instruction sets exist, how assembly relates to machine code, and what it would mean to eventually compile something C-like into a real executable format.

## Fundamental Object

`Program`.

The program is the causal thread through the whole project. It begins as source text and is transformed into progressively more explicit artifacts:

```text
source -> tokens -> parse tree -> AST -> typed AST -> TAC -> machine code -> execution trace -> result
```

The important thing is not that any one stage is clever. The important thing is that each stage owns one kind of truth and hands a stable artifact to the next stage.

## Why This Fits

Compiler Lab connects several existing interests:

- the language/toolchain side of IRATA,
- the abstraction-risk lessons from Pysh,
- the proof and artifact discipline from IRATA2,
- the "not being stuck" loop of building one verified stage at a time,
- the desire to learn fundamentals rather than jump straight to a complex language.
- the historical curiosity of moving from source language to IR to assembly to executable code.

It also has a clear way to avoid the old Pysh failure mode: do not build an open-ended parser framework first. Build one tiny language and one complete pipeline.

## Non-Goals

- Do not start with a general parser framework.
- Do not start with a large language.
- Do not start with optimization passes.
- Do not start with LLVM.
- Do not start with a JIT.
- Do not start with a REPL.
- Do not start with a full standard library.
- Do not start with C.
- Do not start with ELF.
- Do not make syntax design the whole project.

V1 should not include classes, closures, modules, generics, borrow checking, macros, garbage collection, or complex runtime behavior.

## V1 Thesis

The smallest worthwhile v1 is a complete compiler for a tiny expression-and-statement language that lowers to three-address code and runs on a tiny VM or machine-code environment.

V1 should support:

- integer literals,
- local variables,
- assignment,
- arithmetic,
- comparisons,
- `if`,
- `while`,
- a simple `print` or output instruction,
- deterministic execution,
- test programs with expected output,
- inspectable artifacts at each compiler stage.

The first complete win is compiling and running something like:

```text
x = 1;
sum = 0;
while (x <= 10) {
  sum = sum + x;
  x = x + 1;
}
print sum;
```

and being able to inspect every representation between the source and the result.

## Model Objects

- `SourceFile`: text plus filename/span context.
- `Token`: lexical unit with kind, lexeme, and source span.
- `ParseTree`: grammar-shaped syntax artifact.
- `Ast`: simplified semantic syntax tree.
- `SymbolTable`: names, scopes, and declarations.
- `Type`: small set of language types, probably just `int` and `bool` in v1.
- `TypedAst`: AST decorated with resolved symbols and types.
- `TacInstruction`: three-address operation such as `t1 = x + y`.
- `BasicBlock`: optional later grouping of TAC instructions.
- `MachineInstruction`: lowered instruction for the tiny VM or machine.
- `InstructionSet`: minimal target instruction set used to execute compiled programs.
- `ObjectFile`: later artifact for machine code, symbols, relocations, or executable-format experiments.
- `VmState`: registers, stack, memory, program counter, and output.
- `ExecutionTrace`: structured record of each executed instruction.
- `Diagnostic`: parse, type, and compile errors with source spans.

## First Questions

- Can source text become a token stream with useful spans?
- Can the parser produce a stable artifact without becoming a framework project?
- Can invalid programs produce readable diagnostics?
- Can semantic analysis catch unknown variables and type errors?
- Can AST lower to TAC in a way that teaches compiler design?
- Can TAC lower to a simple instruction set?
- Should the first target be a custom teaching VM, a known educational ISA, or a deliberately tiny standard-ish instruction set?
- Can the VM execute test programs deterministically?
- What does the compiler learn from having a real assembly/machine-code boundary?
- How far can a small C subset go before C itself becomes the project?
- Can every stage be asserted directly in tests?

## First Runnable Moment

The first delightful runnable moment is one compiled program with artifacts:

```text
source:
  x = 2 + 3;
  print x;

tokens:
  IDENT(x) EQUAL INT(2) PLUS INT(3) SEMI PRINT IDENT(x) SEMI

typed ast:
  assign x:int = add(2:int, 3:int)
  print x:int

tac:
  t0 = 2 + 3
  x = t0
  print x

vm:
  LOAD_CONST r0, 2
  LOAD_CONST r1, 3
  ADD r2, r0, r1
  STORE x, r2
  PRINT x

output:
  5
```

That artifact chain is the product.

## Educational Goals

This project should be explicit about what it teaches.

Core concepts to learn in v1:

- lexing and token spans,
- grammar design,
- recursive descent or Pratt parsing,
- AST shape and tree normalization,
- source diagnostics,
- symbol tables and scope,
- simple type checking,
- three-address code,
- labels and branches,
- lowering to an instruction set,
- execution traces,
- program-level tests.

Concepts to learn after v1:

- basic blocks and control-flow graphs,
- liveness,
- register allocation,
- stack frames,
- calling conventions,
- object files,
- linking,
- executable formats,
- interpretation versus compilation,
- JIT compilation.

The project should prefer standard compiler vocabulary where appropriate. If I invent a name for something, it should be because the concept is genuinely different, not because I skipped learning the standard term.

## Target Machine And Instruction Set

The target machine is part of the learning opportunity.

There are three plausible target choices:

1. Custom teaching VM.
   - Easiest to build and inspect.
   - Best for V1 momentum.
   - Risk: it can become another toy CPU if not constrained.
2. Standard minimal educational ISA.
   - More historical and transferable.
   - Forces contact with real assembly concepts.
   - Risk: learning the target can distract from learning the compiler.
3. Real architecture subset.
   - Most direct path toward object files and ELF.
   - Highest complexity and platform-specific detail.
   - Not appropriate for V1.

Recommended V1: define a tiny register VM or stack VM that is intentionally boring and compiler-friendly.

The target should be just rich enough to express TAC:

- load constant,
- load local,
- store local,
- arithmetic,
- comparison,
- conditional jump,
- unconditional jump,
- print/output,
- halt.

After V1, the project can introduce a more standard target or a historical target as a second backend. That would make the compiler architecture real: one frontend, one IR, multiple lowerings.

## Historical Stretch Goals

These are not V1 goals, but they are part of why the project is interesting.

### Compile A C-Like Subset To IR

A good post-v1 milestone would be a tiny C subset:

- `int`,
- local variables,
- expressions,
- `if`,
- `while`,
- functions,
- return values,
- maybe pointers only much later.

The goal would be to understand how C-like syntax maps to AST, types, TAC, control flow, stack frames, and calls.

### Compile C To A Standard IR

A more serious learning milestone would be asking:

> Can I compile a small C subset to a standard-ish IR?

This does not need to mean full LLVM on day one. It could mean learning the shape of a conventional IR: temporaries, blocks, branches, phi-like problems, memory operations, and calls.

### Compile To ELF And Execute It

The most historically satisfying stretch goal:

> Can I compile a tiny program to ELF and execute it?

This should be treated as a separate advanced project layer. It requires learning object-file structure, sections, symbols, relocations, entry points, ABI/calling convention details, and OS interface expectations.

The right first ELF milestone would be very small:

```c
int main() {
  return 42;
}
```

or a no-libc program that exits with a known code.

This is a stretch goal because it shifts the project from compiler fundamentals into systems ABI and executable-format work. That is interesting, but it should be earned.

## Representation Principle

Every compiler stage should produce a real artifact.

Avoid hidden transformations. Avoid a parser that directly mutates a runtime. Avoid diagnostics that require reading logs. The pipeline should be inspectable:

- tokens can be printed and asserted,
- parse trees can be compared,
- AST nodes have stable shapes,
- typed AST records resolved names and types,
- TAC is linear and readable,
- VM instructions are explicit,
- execution traces explain state changes.

This is the antidote to Pysh-style vertical surgery. A change in one stage should have a clear contract with the next.

## Testing Principle

The test suite should be stage-oriented and program-oriented.

Stage tests:

- lexer examples,
- parser examples,
- AST lowering examples,
- diagnostic examples,
- type-checking examples,
- TAC generation examples,
- VM instruction examples.

Program tests:

- source program,
- expected output,
- optional expected TAC or trace,
- expected diagnostics for invalid programs.

Tests should read like tiny compiler lessons. Each one should explain one idea.

## V1 Scope

V1 includes:

- hand-written lexer,
- hand-written parser for a small grammar,
- source spans,
- diagnostics,
- simple AST,
- integer and boolean types,
- local variables,
- assignments,
- arithmetic and comparison expressions,
- `if` and `while`,
- TAC generation,
- tiny VM or machine-code environment,
- explicitly documented minimal instruction set,
- execution trace,
- CLI command to compile/run and optionally dump stages.

V1 excludes:

- parser generator,
- optimizer,
- register allocation beyond a trivial scheme,
- native machine code,
- ELF,
- C frontend,
- JIT,
- garbage collection,
- functions,
- closures,
- classes,
- modules,
- strings beyond maybe output labels,
- complex frontend UI.

## Growth Path

### Layer 1: Source To AST

Build lexer, parser, AST, source spans, and diagnostics.

### Layer 2: Semantics

Add names, scopes, simple types, typed AST, and semantic diagnostics.

### Layer 3: Three-Address Code

Lower typed AST into TAC. Make temporaries, labels, branches, and control flow explicit.

### Layer 4: Tiny Machine

Define a small VM or machine-code environment and lower TAC into executable instructions.

### Layer 5: Program Test Suite

Build a suite of tiny programs that demonstrate language features and compiler stages.

### Layer 6: Standard Compiler Concepts

Add basic blocks, control-flow graphs, liveness, simple register allocation, stack frames, or another concept only after the v1 pipeline is stable.

### Layer 7: Historical Targets

Experiment with a more standard target: a C-like frontend, a standard-ish IR, an assembly backend, object files, or a tiny ELF executable.

### Layer 8: Choose A Direction

After v1, choose one earned direction:

- interpreter with richer runtime,
- JIT-compiled language,
- bytecode VM,
- optimization passes,
- register allocation,
- stack frames and calling conventions,
- C subset frontend,
- ELF executable output,
- richer type system,
- better frontend tooling,
- compile to an existing target.

Do not choose this before v1 has produced stable lessons.

## Fit Analysis

### Fit Score

Compiler Lab is a strong fit if it stays a learning pipeline rather than becoming another parser-framework project.

| Goal | Fit | Notes |
| --- | --- | --- |
| Small deterministic world | Strong | A tiny language and VM can be tightly scoped. |
| One fundamental object | Strong | `Program` flows through every artifact. |
| Causality and explanation | Strong | Each compiler stage explains how the previous stage transformed. |
| Tests as proof | Strong | Stage tests and program tests map directly to the design. |
| Start delightfully small | Strong | `print 5` can produce the whole artifact chain early. |
| Avoid generic-engine trap | Medium | Parser framework and language-design sprawl are serious risks. |
| Personal hook | Strong | It connects IRATA language/toolchain work with Pysh lessons. |
| Execution risk | Medium | V1 is manageable; later C, ELF, JIT, and ABI ambitions can expand fast. |

### Why It Might Be Worth Building

This is a direct way to learn compiler design fundamentals without pretending to design the final language first.

It could repair the Pysh failure mode by making every layer produce a stable artifact. It could also connect naturally to simple machine-code environments and the virtual-computer projects without requiring a full fantasy console.

The historical path is especially appealing: learn the normal compiler pipeline first, then ask increasingly concrete questions about C, IR, assembly, object files, and executable formats.

### Main Risks

- Building a parser framework before building one language.
- Spending too much time on syntax taste.
- Letting the VM become another CPU simulator.
- Adding functions, closures, objects, or modules before TAC and execution are stable.
- Jumping to JIT too early.
- Jumping to C or ELF before the basic compiler pipeline is understood.
- Turning executable formats and ABI details into V1 blockers.

### Scope Guardrails

- V1 must compile one tiny language, not define a language platform.
- V1 must produce TAC.
- V1 must run programs in a small execution environment.
- V1 must document the minimal instruction set it targets.
- V1 must expose every stage as an inspectable artifact.
- V1 must include invalid-program diagnostics.
- V1 must not include JIT, C, ELF, functions, or a complex runtime.

### Recommended Execution Plan

1. Write `README.md` and `docs/design.md` with the tiny grammar and artifact pipeline.
2. Build lexer with source spans and tests.
3. Build parser and AST for assignments, arithmetic, and print.
4. Add diagnostics for syntax errors.
5. Add semantic analysis for variables and simple types.
6. Add TAC generation for straight-line programs.
7. Define the minimal instruction set and document it.
8. Add a tiny VM and execution trace.
9. Add `if` and `while` through labels and branches in TAC.
10. Build program tests that assert output and selected artifacts.
11. Write a v1 postmortem before choosing interpreter, JIT, optimizer, C subset, ELF, or richer language features.

## Relationship To Existing Projects

- `IRATA`: language and machine-code pipeline inspiration.
- `PIRATA` / `IRATA2`: assembly, machine execution, and tests-as-proof discipline.
- `Pysh` family: cautionary history around parser frameworks and vertical abstraction stacks.
- `Sudologue`: proof-style output and human-readable explanation of derived results.
- `NES Emulator`: complementary historical systems work; Compiler Lab moves from source to machine, while NES Emulator models an existing machine's behavior.

Compiler Lab should proceed only if its thesis is "learn compiler fundamentals by producing inspectable artifacts," not "build my dream language immediately."

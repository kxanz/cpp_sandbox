# C++ Sandbox

This repository is my personal C++ practice space. I use it to build a stronger foundation in the language by writing small examples, testing syntax, and documenting concepts as I learn them.

The repo will continue to grow as I practice foundational topics, intermediate ideas, and advanced C++ concepts.


## Goals

- Practice C++ syntax through small focused examples.
- Understand how the compiler interprets different language features.
- Learn safe habits around initialization, types, memory, and program structure.
- Work through *Effective C++* and *Effective Modern C++* item by item, with a runnable example for each.
- Build notes and examples for both foundational and advanced C++ topics.
- Track progress over time in one organized GitHub repository.

## Structure

```
cpp_sandbox/
├── fundamentals/            # Beginner topics: pointers, references, containers, etc.
├── effective_cpp/           # Effective C++ (Meyers) exercises, one folder per chapter
├── effective_modern_cpp/    # Effective Modern C++ (Meyers) exercises, one folder per chapter
├── concurrency/             # Reserved for a future concurrency book
└── cic/                     # Interview-style / coding-challenge practice
```

`effective_cpp/` and `effective_modern_cpp/` are split into chapter folders named `NN_topic` (e.g. `03_resource_management`), matching each book's actual chapter order. Inside each chapter folder, one file per item, named `itemNN_short_slug.cpp` (e.g. `item13_raii.cpp`) — the two-digit item number keeps files sorted in book order regardless of alphabetical filename order.

## How To Build Examples

Every `.cpp` file in this repo is automatically picked up by CMake and built as its own executable — no manual setup needed per file.

```bash
cmake -B build                    # once, or whenever you add a new .cpp file
cmake --build build --target <target_name>
./build/<target_name>
```

The target name for any file is its path relative to the repo root, with `/` replaced by `_` and `.cpp` dropped — e.g. `fundamentals/pointers/pointersnull.cpp` becomes `fundamentals_pointers_pointersnull`.

You can also compile a single file directly, without CMake:

```bash
g++ -std=c++20 fundamentals/variables/initialization.cpp -o initialization
./initialization
```

Some examples are intentionally written to explore compiler errors or undefined behavior. Those files may not compile cleanly, or they may produce unexpected output by design — so building *everything* at once isn't a meaningful health check for this repo; build one target at a time.

## Repository Style

Each folder focuses on one concept or group of related concepts. Files are meant to stay small so each example is easy to read, compile, break, and improve.

## Notes

This is a learning repository, so the code may include experiments, incomplete examples, compiler errors, and intentional mistakes. The purpose is to practice, observe behavior, and improve over time.

# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this repo is

Personal study notes / exercise archive for the **数据结构与算法** (data structures and algorithms) course, following the 王道考研 (Wang Dao postgraduate exam) textbook. Every file is a self-contained C program: no shared headers, no libraries, each one implements a single data structure or algorithm with its own `main()` that prints a demo.

## Build

CLion + CMake project, C17. Each source file is its own executable target in `CMakeLists.txt` (Ninja generator, builds into `cmake-build-debug/`). Open in CLion to build/run, or from the command line:

```bash
cmake -S . -B cmake-build-debug -G Ninja
cmake --build cmake-build-debug
# run one exercise
cmake --build cmake-build-debug --target p56_hash-table
./cmake-build-debug/p56_hash-table.exe
```

There is no test framework — correctness is shown by each program's printed output.

## Structure

Source is organized by topic directory, and every `add_executable(...)` target is named `p<page>_<name>` where `<page>` refers to the textbook page/section:

- `linear-list/` — 线性表: sequence list, linked list (single/double/circular), stack, queue, priority queue
- `tree/` — 树: binary tree (build/traversal), threaded tree, BST, balanced tree, Huffman, heap
- `hash-table/` — 散列表: hash table, linear probing, chain address
- `graph/` — 图: adjacency matrix/list, DFS, BFS, Prim, Kruskal, Dijkstra, Floyd, topological sort (Kahn)
- `disjoint-set-union/` — 并查集
- `binary_search.c` — 二分搜索
- `main.c` — the CLion "Hello, World!" template, unused otherwise
- `encodeproblem` — scratch note (no `.c` extension) about Windows console UTF-8 output via `SetConsoleOutputCP(65001)`; not in the build

## Conventions

- `typedef int T;` for the element type; `typedef struct Xxx * Node;` aliases a struct pointer as `Node`.
- Comments are written in Chinese; each file starts with a CLion-generated `// Created by zyh on ...` header.
- To add a new exercise: create the `.c` file in the matching topic directory, then add an `add_executable(pNN_name path/to/file.c)` line to `CMakeLists.txt` under the correct topic comment block. CLion auto-reloads CMake.

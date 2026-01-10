# DS-Algorithms

A curated collection of data structures and algorithms implemented in C++.  
This repository is intended as a learning resource, reference, and playground for students and engineers to study, run, and contribute implementations, tests, and example usages.

- Primary language: C++ (100%)
- Status: Active — contributions welcome

---

## Table of Contents

- [Project goals](#project-goals)
- [Repository layout](#repository-layout)
- [Supported algorithms & data structures](#supported-algorithms--data-structures)
- [Complete list of algorithms and function names (suggested)](#complete-list-of-algorithms-and-function-names-suggested)
- [Getting started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Clone](#clone)
  - [Build (CMake)](#build-cmake)
  - [Build single file (g++)](#build-single-file-g)
  - [Run examples & tests](#run-examples--tests)
- [How to add a new algorithm or data structure](#how-to-add-a-new-algorithm-or-data-structure)
- [Coding conventions & style](#coding-conventions--style)
- [Testing strategy](#testing-strategy)
- [Contributing](#contributing)
- [Issue & PR process](#issue--pr-process)
- [Roadmap](#roadmap)
- [Contact & acknowledgements](#contact--acknowledgements)

---

## Project goals

- Provide clean, well-documented implementations of common data structures and algorithms in modern C++.
- Offer small, reproducible example programs and tests for each implementation.
- Serve as an educational resource: clear code, comments explaining time/space complexity and invariants.
- Be contributor-friendly: clear guidelines for adding new content and tests.

---

## Repository layout

This is a suggested, conventional layout used by the repo. If the repo currently uses a slightly different layout, use this as the target structure.

- /algorithms
  - /sorting
  - /searching
  - /graph
  - /dp
  - /greedy
- /data_structures
  - /arrays
  - /linked_list
  - /stack
  - /queue
  - /heap
  - /Max heap
  - /tree
  - /hash
- /examples
  - small programs showing how to use implementations
- /tests
  - unit tests (GoogleTest or custom harness)
- /include (optional)
  - header-only reusable components
- /benchmarks (optional)
  - micro-benchmarks comparing implementations
- CMakeLists.txt
- .clang-format
- .github/
  - ISSUE_TEMPLATE.md
  - PULL_REQUEST_TEMPLATE.md
  - workflows/ (CI configs)
- README.md
- LICENSE

Note: The repo is C++-only (100% C++). Use modern C++ features responsibly, with portability in mind.

---

## Supported algorithms & data structures

Examples of the kinds of implementations you will find (or are encouraged to add):

- Data structures:
  - Arrays, dynamic arrays (vector-like)
  - Singly/doubly circular linked lists
  - Stacks, queues, deque
  - Hash tables (open addressing / chaining)
  - Binary trees, BST, AVL, Red-Black Trees (optional)
  - Heaps (binary heap, priority queue)
  - Tries
  - Disjoint Set Union (Union-Find)
  - Segment trees, Fenwick trees (BIT)
- Algorithms:
  - Sorting: QuickSort, MergeSort, HeapSort, CountingSort, RadixSort, Insertion/Selection/Bubble (for teaching)
  - Searching: Binary search and variants
  - Graph: BFS, DFS, Dijkstra, Bellman-Ford, Floyd-Warshall, Topological sort, MST (Kruskal, Prim)
  - String: KMP, Rabin-Karp, Z-algorithm, suffix array basics
  - Dynamic Programming: common patterns and classic problems
  - Greedy algorithms and examples
  - Backtracking / DFS templates
  - Complexity analysis notes for each implementation

---

## Complete list of algorithms and function names (suggested)

Below is a comprehensive, organized list of algorithm/data-structure names and suggested public function names & signatures (C++-style) that you can include in the repository. Use these as naming examples or reference APIs when adding implementations to the repo. If you want, I can scan the repository and extract the actual function names used in your code—ask me to do that and I'll list them exactly as found.

Note: these are suggested names and signatures intended to be consistent and easy to use. Implementations may instead use classes, namespaces, or overloaded templates depending on design choices.

- General utilities
  - gcd(a, b) -> long long
  - lcm(a, b) -> long long
  - mod_pow(base, exp, mod) -> long long
  - mod_inv(a, mod) -> long long
  - sieve_eratosthenes(n) -> vector<int>
  - is_prime(n) -> bool
  - pow_int(base, exp) -> long long

- Sorting
  - quick_sort(vector<T>& a)
  - quick_sort_range(vector<T>& a, int l, int r)
  - merge_sort(vector<T>& a)
  - merge_sort_range(vector<T>& a, int l, int r)
  - heap_sort(vector<T>& a)
  - counting_sort(vector<int>& a, int max_value)
  - radix_sort(vector<int>& a)
  - insertion_sort(vector<T>& a)
  - selection_sort(vector<T>& a)
  - bubble_sort(vector<T>& a)
  - std_heapify(vector<T>& a) / make_heap_like

- Searching
  - binary_search(const vector<T>& a, T target) -> int  // returns index or -1
  - lower_bound(const vector<T>& a, T target) -> int
  - upper_bound(const vector<T>& a, T target) -> int
  - ternary_search(function<double(double)> f, double lo, double hi) -> double

- Arrays & Sequences
  - two_sum_indices(vector<int>& a, int target) -> pair<int,int>
  - prefix_sum(vector<T>& a) -> vector<T>
  - sliding_window_max(vector<int>& a, int k) -> vector<int>

- Linked Lists
  - class SinglyLinkedList { push_front(T), push_back(T), pop_front(), remove(value), find(value), reverse(), size() }
  - class DoublyLinkedList { push_front, push_back, pop_back, insert_after(node, val), erase(node) }
  - merge_two_sorted_lists(Node* l1, Node* l2) -> Node*

- Stack & Queue
  - class Stack<T> { push(T), pop(), top(), empty(), size() }
  - class Queue<T> { enqueue(T), dequeue(), front(), back(), empty(), size() }
  - class Deque<T> { push_front, push_back, pop_front, pop_back, front, back }
  - min_stack: MinStack { push, pop, top, get_min }

- Heap / Priority Queue
  - BinaryHeap<T> { push, pop, top, build_heap(vector<T>& a) }
  - push_heap(vector<T>& a)
  - pop_heap(vector<T>& a)

- Trees
  - BinaryTree traversal functions:
    - inorder(TreeNode* root, function)
    - preorder(TreeNode* root, function)
    - postorder(TreeNode* root, function)
  - class BST { insert(key), remove(key), find(key), min(), max(), lower_bound(key) }
  - AVLTree { insert(key), remove(key), find(key), rotate_left(node), rotate_right(node) }
  - RedBlackTree { insert, remove, find } (API similar to BST)
  - SegmentTree { build(vector<T>), update(index, value), query(l, r) }
  - FenwickTree/BIT { Fenwick(int n); add(idx, delta); sum(idx); range_sum(l, r) }
  - Trie / Prefix Tree { insert(string), search(string) -> bool, starts_with(prefix) -> bool, erase(string) }

- Hashing
  - unordered_map-like usage examples
  - custom_hash_table { insert(key, value), erase(key), find(key), contains(key) }
  - rolling_hash / rabin_karp_hash functions

- Disjoint Set / Union-Find
  - class DisjointSet { make_set(n), find_set(x), union_sets(a,b), connected(a,b) }

- Graphs
  - Graph adjacency list representation: Graph { add_edge(u,v,weight=1), neighbors(u) }
  - BFS:
    - bfs(Graph& g, int src) -> vector<int> dist or parent
  - DFS:
    - dfs(Graph& g, int src) -> traversal order, parent arrays
  - Dijkstra:
    - dijkstra(Graph& g, int src) -> vector<long long> dist
  - Bellman-Ford:
    - bellman_ford(Graph& g, int src) -> pair<bool, vector<long long>> (bool indicates negative cycle)
  - Floyd-Warshall:
    - floyd_warshall(matrix) -> matrix (all-pairs shortest paths)
  - Minimum Spanning Tree:
    - kruskal(edges, n) -> vector<Edge> mst, total_weight
    - prim(Graph& g, int src) -> total_weight, parent array
  - Topological sort:
    - topo_sort(Graph& g) -> vector<int> order
  - Strongly connected components:
    - kosaraju(Graph& g) -> vector<vector<int>> sccs
    - tarjan_scc(Graph& g) -> vector<vector<int>> sccs
  - Minimum cut / flow examples (optional): edmonds_karp, dinic

- Shortest Paths / Advanced
  - spfa(Graph& g, int src) -> dist (if used)
  - multi_source_bfs(vector<int> sources)

- Strings & Pattern Matching
  - kmp_prefix_function(const string& s) -> vector<int>
  - kmp_search(const string& text, const string& pattern) -> vector<int> matches
  - z_function(const string& s) -> vector<int>
  - rabin_karp(const string& text, const string& pattern) -> vector<int>
  - manacher(const string& s) -> vector<int> palindrome_radii
  - build_suffix_array(const string& s) -> vector<int> sa
  - build_lcp_array(const string& s, const vector<int>& sa) -> vector<int> lcp

- Dynamic Programming (classic problems & templates)
  - knapsack_01(values, weights, W) -> max_value
  - unbounded_knapsack(values, weights, W)
  - longest_increasing_subsequence(vector<T>& a) -> length (and optionally sequence)
  - longest_common_subsequence(string a, string b) -> length / sequence
  - edit_distance(string a, string b) -> int
  - coin_change_min_coins(coins, amount) -> int
  - dp_grid_paths(m, n) -> number of paths (with obstacles variants)

- Greedy & Interval
  - activity_selection(vector<pair<int,int>> intervals) -> selected_intervals
  - fractional_knapsack(items, capacity) -> max_value
  - interval_scheduling, merge_intervals

- Backtracking & Search templates
  - n_queens(n) -> vector<vector<int>> solutions
  - sudoku_solver(board) -> solved board
  - subset_sum_backtracking(arr, target) -> bool / list of subsets
  - generate_permutations(vector<T> a) -> list / iterator

- Mathematics & Number Theory
  - extended_gcd(a, b) -> (g, x, y)
  - modular_exponentiation(base, exp, mod) -> long long
  - modular_inverse(a, mod) -> long long
  - euler_phi(n) -> int
  - is_palindrome_number(n) -> bool

- Geometry
  - point structure, vector ops
  - cross(a,b), dot(a,b)
  - convex_hull_graham_scan(points) -> hull
  - convex_hull_monotone_chain(points) -> hull
  - polygon_area(points) -> double
  - closest_pair_of_points(points) -> pair of points or distance

- Misc / Competitive Programming helpers
  - bit_count(x) -> int
  - highest_bit(x) -> int
  - lower_power_of_two(x) -> int
  - next_permutation usage examples
  - random_shuffle / rng helpers (seeded)

- Example APIs for test harnesses
  - run_all_tests() -> exit code 0 on success
  - TEST macro guidance (if using GoogleTest)
  - small main() wrappers in /examples demonstrating each algorithm

---

## Getting started

### Prerequisites

- A C++ compiler supporting at least C++17 (g++ 9+, clang 9+, MSVC 2019+). We recommend using C++17 or C++20 where applicable.
- CMake (>= 3.10 recommended; >= 3.16 preferred for newer features)
- Ninja or GNU Make (optional)
- Git

Optional (for tests):
- GoogleTest (the CMake setup can fetch it automatically)

### Clone

```bash
git clone https://github.com/Mohammed-Bahr/DS-Algorithms.git
cd DS-Algorithms
```

### Build (CMake) — recommended

This repository is structured to be built with CMake. Example:

```bash
# Create a build directory
mkdir -p build && cd build

# Configure (use Ninja or Unix Makefiles)
cmake -S .. -B . -DCMAKE_BUILD_TYPE=Release

# Build all
cmake --build .

# Run tests (if tests are configured)
ctest --output-on-failure
```

To build with a specific generator and build type:

```bash
cmake -S .. -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Build single file (g++)

For quick experiments you can compile single example files:

```bash
# Example: compile example program
g++ -std=c++17 -O2 -Wall examples/sorting_demo.cpp -o bin/sorting_demo
./bin/sorting_demo
```

Add include paths if implementation headers are in `include/`:

```bash
g++ -std=c++17 -Iinclude -O2 -Wall examples/example.cpp -o example
```

### Run examples & tests

- Examples live in `/examples`. Build them via the CMake target `examples` (if present) or compile directly with g++.
- Tests live in `/tests`. If CMake is configured to build and run tests, use `ctest` in the build directory:
  - `ctest -V` for verbose output
  - `ctest -j` to run tests in parallel

---

## How to add a new algorithm or data structure

1. Create a subfolder under `algorithms/` or `data_structures/` following the existing organization.
2. Provide:
   - Implementation file(s) (.cpp and/or header .hpp/.h)
   - A minimal example in `/examples` demonstrating usage
   - Unit tests in `/tests` with clear assertions and edge cases
   - A short README or header comment explaining:
     - Problem or data structure description
     - API / public functions and expected inputs/outputs
     - Time and space complexity
3. Follow naming conventions:
   - filenames: lowercase with underscores, e.g., `binary_search.cpp`, `segment_tree.hpp`
   - namespaces: use `dsalg` or `dsalg::<subsystem>` (optional but recommended)
4. Ensure code compiles with the project's build system (CMake; add new files to CMakeLists as necessary).
5. Add documentation comments and references to sources (paper/URL) where appropriate.
6. Open a pull request describing the algorithm, complexity, and test coverage.

---

## Coding conventions & style

- Language standard: Prefer C++17 (or C++20 where justified). Document standard in CMakeLists or CONTRIBUTING.
- Formatting: Use clang-format. Provide `.clang-format` at repository root. Example rules:
  - Column width: 100
  - Use `LLVM` or `Google` style as baseline
- Naming:
  - Types and classes: PascalCase or CamelCase
  - Functions and variables: snake_case or lowerCamelCase consistently across the repo
  - Filenames: lowercase_with_underscores.cpp / .hpp
- Documentation:
  - Public classes and functions should have a short Doxygen-style comment block describing behavior and complexity.
- Error handling:
  - Prefer exceptions for unrecoverable errors, or return optional / expected types for functions that may fail (where appropriate).
- Tests:
  - Tests should be deterministic and cover typical, boundary, and edge cases.

Example clang-format invocation:

```bash
clang-format -i $(git ls-files '*.cpp' '*.hpp' | tr '\n' ' ')
```

---

## Testing strategy

- Prefer unit tests for each algorithm with clear, small cases and some randomized tests to catch edge-cases.
- Use GoogleTest (gtest) or a lightweight custom test harness if required.
- Tests should be fast; longer integration or benchmark tests should be optional and excluded from the default test run.
- Add CI checks to run formatting, build, and tests on PRs (GitHub Actions recommended).

Example (CMake snippet for tests):

```cmake
# In tests/CMakeLists.txt
find_package(GTest REQUIRED)
add_executable(test_heap test_heap.cpp)
target_link_libraries(test_heap PRIVATE GTest::gtest_main)
add_test(NAME heap_tests COMMAND test_heap)
```

---

## Contributing

Contributions are very welcome! Suggested workflow:

1. Fork the repository.
2. Create a branch named `topic/<short-description>` (e.g., `feature/segment-tree`).
3. Make changes in your branch. Add tests and examples.
4. Ensure `clang-format` and unit tests pass locally.
5. Open a Pull Request to the main repository. In the PR description:
   - Explain the change, include complexity analysis, and link to references.
   - Include sample usage and test results (if applicable).
6. Be responsive to code review comments and update the PR as requested.

Please follow the [Issue & PR process](#issue--pr-process) below.

---

## Issue & PR process

- Issues
  - Use issues to propose new algorithms, report bugs, or request improvements.
  - Provide a clear title, a short description, and steps to reproduce if relevant.
- Pull Requests
  - Small, focused PRs are easier to review.
  - Include tests/examples for new functionality.
  - Use descriptive commit messages and keep commits logically grouped.
  - Link related issues in the PR body using `#issue-number`.

Suggested commit message format (Conventional-ish):

```
type(scope): short summary

optional longer description explaining the why, linkage, and details
```

Types: feat, fix, docs, test, refactor, chore

---

## Roadmap

Possible improvements and ongoing work:

- Complete implementations of balanced BSTs (AVL, Red-Black)
- More graph algorithms and advanced string algorithms (suffix automata, suffix trees)
- Benchmarks comparing algorithms across inputs
- Visualizations for selected algorithms (separate docs/web page)
- Classroom-friendly "explainers" for each algorithm with diagrams and step-by-step walkthroughs

If you want to help prioritize, open an issue or start a discussion.

---

## Contact & acknowledgements

Maintainer: Mohammed-Bahr

If you have questions, open an issue, or send a PR. For larger discussions, consider opening a Discussion (if enabled) or linking to an issue with the proposal.

Acknowledgements:
- Many algorithm ideas and implementations are adapted from standard textbooks, competitive programming resources, and open educational projects. Individual files should contain attributions and references where appropriate.

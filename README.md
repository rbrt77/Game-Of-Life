# Conway's Game of Life in C

Command-line implementation of Conway's Game of Life, built for the *Proiectarea algoritmilor* course (UPB, 2025). It simulates generations on a character grid and stores the history with queues of changed cells, a binary tree and, in the bonus, a stack of lists.

**Status:** Tasks 1-3 and the bonus are implemented; Task 4 (Hamiltonian chains) is not. The reference tests provided by the course (tests 1-15) pass.

| Task | What it does | Status |
|------|--------------|--------|
| 1 | Applies the standard rules for K generations on an N x M grid (`X` alive, `+` dead) | Done |
| 2 | Stores only the cells that change state in each generation, as a queue of coordinate lists | Done |
| 3 | Builds a binary tree of generations (left child: rule B, right child: standard rules) and prints it in preorder | Done |
| Bonus | Rebuilds generation 0 from the final grid and the per-generation change lists | Done |
| 4 | Hamiltonian chains in the generation graphs | Not implemented |

Rule B (the alternative rule): a cell with exactly two living neighbours becomes alive; every other cell keeps its state.

## Build and run

Requires `gcc` and `make` (Linux or WSL).

```bash
make
./test input.txt output.txt
```

Bonus (separate program):

```bash
gcc -Wall -Wextra -std=c99 taskbonus.c -o bonus
./bonus bonus_input.txt bonus_output.txt
```

## Input format

```
T           task number (1, 2 or 3)
N M         grid size
K           number of generations
<N lines>   initial grid
```

Bonus input: `T`, `N M`, `K`, then for each of the K generations a count followed by that many `(row,col)` pairs, then the final grid.

## Example (Task 3, K = 1)

Input:

```
3
6 6
1
++++++
++++X+
++XX++
+++X++
+X++++
++++++
```

Output: generation 0, then generation 1 with rule B, then generation 1 with the standard rules (preorder walk of the tree), separated by blank lines:

```
++++++
++++X+
++XX++
+++X++
+X++++
++++++

++++++
++X+X+
++XX++
+X+XX+
+XX+++
++++++

++++++
+++X++
++XXX+
+++X++
++++++
++++++
```

## How it works

- **Grid:** a `char**` matrix; `numarare` counts the eight neighbours of a cell.
- **Task 2:** for every generation, the coordinates of the cells that changed are collected in a queue and written to the output (`schimbare2`). The statement suggests a stack of lists; a queue was used here and accepted.
- **Task 3:** each tree node (`Arbore`) holds the queue of cells that changed relative to its parent; the root holds the living cells of generation 0. `creare` builds the children from copies of the parent grid, the left one with `schimbare3st` (rule B) and the right one with `schimbare3dr` (standard rules). `afisare3pre` walks the tree in preorder, applies each node's changes to a copy of its parent's grid and prints it.
- **Bonus:** the change lists are pushed onto a stack of lists; popping from the top and flipping each listed cell on the final grid recovers generation 0 (`taskbonus.c`).

## Limitations

- The tree has 2^K nodes, so Task 3 is meant for small K.
- Input files are assumed to follow the format above (no validation of malformed input).
- The Task 3 construction was fixed after the course deadline; the version submitted in May 2025 is tagged `predat-2025-05-28`.

## Files

- `tema.c` - main program (Tasks 1-3)
- `functii.c`, `functiigof.h` - grid, queue and tree functions
- `taskbonus.c` - bonus program
- `Makefile` - builds `test`
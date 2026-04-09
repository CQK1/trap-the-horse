# Enclosed Horse

A C++ program that approximates an optimal solution to the Enclosed Horse problem a combinatorial optimization problem that is NP-Hard in the general case.

## The Game

Enclosed Horse is played on a rectangular grid where each cell is one of four tile types:

| Value | Tile | Description |
|-------|------|-------------|
| `0` | Grass | Open land — the horse can move freely through these tiles |
| `1` | Water | Impassable — the horse cannot cross water |
| `2` | Horse | The horse's starting position — there is exactly one per map |
| `3` | Wall | Placed by the player — blocks the horse just like water |

The player is given a limited number of walls to place on grass tiles. The goal is to use those walls to completely enclose the horse so it cannot reach the border of the map, while maximizing the area trapped inside the enclosure.

Trapping the horse with any enclosure is straightforward, the challenge is doing it with the **largest possible enclosed area** under a wall budget. This is what makes the problem hard.

## Why It Is NP-Hard

Finding the optimal wall placement that maximizes enclosed area under a fixed wall budget is NP-Hard. The number of possible placements grows combinatorially with the size of the map exhaustively checking every combination of grass tiles quickly becomes computationally infeasible on any non-trivial map.

## Our Approach

Rather than attempting to solve the problem directly over all grass tiles, we reduce the search space before passing it to the solver.

The key insight is that **any valid enclosure must cut off every shortest path from the border to the horse**. We use multi-source Dijkstra's algorithm to find all shortest paths from every border `0` tile to the horse, then collect every tile that appears on any of those paths into a deduplicated vector.

This vector, rather than the full set of grass tiles is what gets fed into the solver. This reduces the effective `n` in the solver's complexity from the total number of grass tiles down to only the tiles that matter, making the solver tractable on maps where a brute force approach would not be.

### Step by Step

1. Every `0` tile on the border is treated as a source node
2. Multi-source Dijkstra's runs simultaneously from all sources, following only `0` tiles
3. All shortest paths to the horse are traced back
4. Every tile appearing on any shortest path is collected into a vector with no duplicates
5. That vector is handed to the solver as the candidate wall placements

## Build and Run

**Requirements:** g++, C++17, macOS or Linux

**Build all drivers:**
```bash
make
```

**Build a specific driver:**
```bash
make d1
```

**Run:**
```bash
./d1
```

**Clean build artifacts:**
```bash
make clean
```
#include "Dijkstra.h"
#include <queue>
#include <set>
#include <tuple>

std::vector<std::pair<int, int>> Dijkstra::findCandiateWalls(const Map& map) {
    // Implementation for finding candidate walls
    int rows = map.rows();
    int cols = map.cols();
    std::pair<int, int> horse = map.horsePos();

    // Set INF to a large value for initialization
    const int INF = 1e9;
    // Initialize distance matrix with INF
    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INF));

    // Initialize parents matrix to store the path
    std::vector<std::vector<std::vector<std::pair<int, int>>>> parents(
        rows, std::vector<std::vector<std::pair<int, int>>>(cols)
    );

    // Priority queue for Dijkstra's algorithm
    using Node = std::tuple<int, int, int>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // Only consider the boundary cells that are grass (0) as starting points
            if ((r == 0 || r == rows - 1 || c == 0 || c == cols - 1) && map.at(r, c) == 0) {
                dist[r][c] = 0;
                pq.push({0, r, c});
            }
        }
    }

    // up down left right directions
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Start to find the shortest path from the boundary to the horse using Dijkstra's algorithm
    while (!pq.empty()) {
        auto [d, r, c] = pq.top();
        pq.pop();

        // If the distance is greater than the recorded distance, skip this node
        if (d > dist[r][c]) continue;

        // check the four directions
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // Only consider cells within the map boundaries and accessible cells (grass or horse)
            if (map.inBounds(nr, nc) && (map.at(nr, nc) == 0 || map.at(nr, nc) == 2)) {
                int new_dist = d + 1;

                // Case A: Found a shorter path to the new cell
                if (new_dist < dist[nr][nc]) {
                    dist[nr][nc] = new_dist;     // Update the distance to the new cell
                    parents[nr][nc].clear();     // Clear previous paths since we found a shorter one
                    parents[nr][nc].push_back({r, c}); // Record the path to the new cell
                    pq.push({new_dist, nr, nc}); // Push the new cell into the priority queue for further exploration
                }
                // Case B: Found a path with the same distance (tie)
                else if (new_dist == dist[nr][nc]) {
                    parents[nr][nc].push_back({r, c}); // Record the additional path to the new cell without clearing previous paths, since it's a tie
                }
            }
        }
    }

    // Now we have the shortest distance from the boundary to the horse and all the paths that lead to it. Backtrack from the horse's position to find all the cells that are on any of these shortest paths.
    std::vector<std::pair<int, int>> result;
    std::set<std::pair<int, int>> visited; // to avoid processing the same cell multiple times during backtracking
    std::queue<std::pair<int, int>> back_q;

    // If the horse is unreachable (distance is still INF), return an empty list immediately
    if (dist[horse.first][horse.second] == INF) {
        return result; // No candidate walls since the horse is unreachable
    }

    // Start backtracking from the horse's position
    back_q.push(horse);
    visited.insert(horse);

    while (!back_q.empty()) {
        auto [r, c] = back_q.front();
        back_q.pop();

        // If this cell is not the horse's position, add it to the result list as a candidate wall
        if (r != horse.first || c != horse.second) {
            result.push_back({r, c});
        }

        // Explore all parent cells that lead to the current cell
        for (auto p : parents[r][c]) {
            if (visited.find(p) == visited.end()) {
                visited.insert(p); // Mark this parent cell as visited to avoid processing it multiple times
                back_q.push(p);
            }
        }
    }
    return result;
}
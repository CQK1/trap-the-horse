#pragma once
#include "Map.h"
#include <vector>
#include <utility>

class Dijkstra {

public:
    static std::vector<std::pair<int, int>> findCandiateWalls(const Map& map);
};
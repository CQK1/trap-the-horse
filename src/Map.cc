#include "Map.h"

Map::Map(const std::vector<std::vector<int>>& grid) {
    _grid = grid;
    _rows = grid.size();
    _cols = grid[0].size();

    // scan once at construction so horsePos() is O(1) later
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols; c++) {
            if (_grid[r][c] == 2) {
                _horse = {r, c};
            }
        }
    }
}

int Map::rows() const {
    return _rows;
}

int Map::cols() const {
    return _cols;
}

int Map::at(int row, int col) const {
    return _grid[row][col];
}

bool Map::inBounds(int row, int col) const {
    return row >= 0 && row < _rows && col >= 0 && col < _cols;
}

std::pair<int,int> Map::horsePos() const {
    return _horse;
}

void Map::display() const {
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols; c++) {
            std::cout << _grid[r][c] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
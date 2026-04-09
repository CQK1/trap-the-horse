#pragma once
#include <vector>
#include <iostream>

class Map {
 public:
  Map(const std::vector<std::vector<int>>& grid);
  
  int rows() const;
  int cols() const;
  int at(int row, int col) const;
  bool inBounds(int row, int col) const;

  std::pair<int,int> horsePos() const;

  void display() const;

  private:

  std::vector<std::vector<int>> _grid;
  int _rows;
  int _cols;
  std::pair<int,int> _horse;
};
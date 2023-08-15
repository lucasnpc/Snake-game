#include <vector>
#include <algorithm>

enum class State { kEmpty, kClosed, kPath, kStart, kFinish };

const int delta[4][2]{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

bool isNeighbor(int currentRow, int currentCol, int neighborRow, int neighborCol) {
  // Check if the given position is within one cell of the current head position
  if (abs(currentRow - neighborRow) <= 1 && abs(currentCol - neighborCol) <= 1) {
    // Check if the given position is not the same as the current head position
    if (currentRow != neighborRow || currentCol != neighborCol) {
      return true; // The given position is a neighbor
    }
  }
  return false; // The given position is not a neighbor
}

bool Compare(const std::vector<int> a, const std::vector<int> b) {
  int f1 = a[2] + a[3]; // f1 = g1 + h1
  int f2 = b[2] + b[3]; // f2 = g2 + h2
  return f1 > f2;
};

void CellSort(std::vector<std::vector<int>>* v) {
  std::sort(v->begin(), v->end(), Compare);
};

int Heuristic(int x1, int y1, int x2, int y2) {
  return std::abs(x2 - x1) + std::abs(y2 - y1);
};

bool CheckValidCell(int x, int y, std::vector<std::vector<State>>& grid) {
  bool on_grid_x = (x >= 0 && x < grid.size());
  bool on_grid_y = (y >= 0 && y < grid[0].size());
  if (on_grid_x && on_grid_y)
    return grid[x][y] == State::kEmpty;
  return false;
};

void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>>& openlist, std::vector<std::vector<State>>& grid) {
  // Add node to open vector, and mark grid cell as closed.
  openlist.push_back(std::vector<int>{x, y, g, h});
  grid[x][y] = State::kClosed;
};

void ExpandNeighbors(const std::vector<int>& current, int goal[2], std::vector<std::vector<int>>& openlist, std::vector<std::vector<State>>& grid) {
  // Get current node's data.
  int x = current[0];
  int y = current[1];
  int g = current[2];

  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++) {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (CheckValidCell(x2, y2, grid)) {
      // Increment g value and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(x2, y2, g2, h2, openlist, grid);
    }
  }
};

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid, int init[2], int goal[2]) {
  // Create the vector of open nodes.
  std::vector<std::vector<int>> open{};

  // Initialize the starting node.
  int x = init[0];
  int y = init[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  AddToOpen(x, y, g, h, open, grid);

  while (open.size() > 0) {
    // Get the next node
    CellSort(&open);
    auto current = open.back();
    open.pop_back();
    x = current[0];
    y = current[1];
    grid[x][y] = State::kPath;

    // Check if we're done.
    if (x == goal[0] && y == goal[1]) {
      grid[init[0]][init[1]] = State::kStart;
      grid[goal[0]][goal[1]] = State::kPath;
      return grid;
    }

    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(current, goal, open, grid);
  }

  // We've run out of new nodes to explore and haven't found a path.
  return std::vector<std::vector<State>>{};
};

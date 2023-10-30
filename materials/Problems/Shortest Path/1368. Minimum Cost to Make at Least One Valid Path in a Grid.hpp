#include "../../libs.hpp"

// LeetCode problem description:
// https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/

// Commenting the code below

class Solution {
public:
  // Function to find the minimum cost to reach the bottom-right cell in a grid
  int minCost(vector<vector<int>> &grid) {
    deque<pair<pair<int, int>, int>> q{
        {{0, 0}, 0}};                        // Initialize a deque for BFS
    int m = grid.size(), n = grid[0].size(); // Get the dimensions of the grid
    unordered_set<int> visited; // Set to keep track of visited cells
    int dirs[4][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // Possible move directions

    while (!q.empty()) {
      auto p = q.front(); // Get the front element of the queue
      int from_i = p.first.first;
      int from_j = p.first.second;
      int cost = p.second;

      if (from_i == m - 1 && from_j == n - 1) {
        return cost; // If we reached the destination, return the cost
      }
      q.pop_front(); // Remove the processed cell from the queue

      visited.insert(from_i * n + from_j); // Mark the cell as visited
      int dir_ind = 1;

      // Iterate through the possible move directions
      for (auto dir : dirs) {
        int to_i = from_i + dir[0];
        int to_j = from_j + dir[1];

        // Check if the move is within bounds and if the cell is not visited
        if (!(0 <= to_i && to_i < m && 0 <= to_j && to_j < n) ||
            visited.find(to_i * n + to_j) != visited.end()) {
          ++dir_ind;
          continue;
        }

        // Adjust the direction index based on the grid value
        if (dir_ind == grid[from_i][from_j]) {
          q.push_front({{to_i, to_j}, cost});
        } else {
          q.push_back({{to_i, to_j}, cost + 1});
        }
        ++dir_ind;
      }
    }
    return 0; // If no path is found, return 0 as the result
  }
};
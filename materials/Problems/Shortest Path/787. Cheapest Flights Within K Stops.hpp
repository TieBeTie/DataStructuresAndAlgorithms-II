#include "../../libs.hpp"

// LeetCode problem description:
// https://leetcode.com/problems/cheapest-flights-within-k-stops/

class Solution {
public:
  // Define a struct to represent a path with cost, stops, and vertex
  // information
  struct Path {
    int cost;
    int stops;
    int v;
    // The operator<=>() is a C++20 feature used for defining comparison between
    // Path objects. It is used to compare two Path objects for ordering in the
    // priority queue.
    auto operator<=>(const Path &) const = default;
  };

  // Function to find the cheapest price from src to dst with a maximum of k
  // stops
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                        int k) {
    // Create an adjacency list to represent the flights
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < flights.size(); ++i) {
      g[flights[i][0]].push_back({flights[i][1], flights[i][2]});
    }

    // Initialize a vector to track the minimum stops to each vertex
    vector<int> min_stops(n, INT_MAX);

    // Use a priority queue to explore paths in order of cost
    // std::greater is a standard C++ template class used as a comparison
    // function object. It works with operator<=>() by inverting the comparison
    // order, making the priority queue behave as a min-heap (smallest element
    // on top) instead of a max-heap.
    priority_queue<Path, vector<Path>, std::greater<>> Q;
    Q.push({0, 0, src});

    while (!Q.empty()) {
      // Get the path with the minimum cost
      Path min_cost_edge = Q.top();
      Q.pop();

      int current_stops = min_cost_edge.stops;
      int current_cost = min_cost_edge.cost;
      int current_vertex = min_cost_edge.v;

      // If the destination is reached, return the current cost
      if (current_vertex == dst) {
        return current_cost;
      }

      // If a better path to the current vertex already exists, skip it
      if (min_stops[current_vertex] < current_stops) {
        continue;
      }
      min_stops[current_vertex] = current_stops;

      // If the maximum stops limit is reached, skip this path
      if (k < current_stops) {
        continue;
      }

      // Explore neighbors and add their information to the priority queue
      for (pair<int, int> &current_edge : g[current_vertex]) {
        int next_vertex = current_edge.first;
        int next_cost = current_edge.second;
        Q.push({current_cost + next_cost, current_stops + 1, next_vertex});
      }
    }
    // If no valid path is found, return -1
    return -1;
  }
};

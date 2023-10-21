#include "../../libs.hpp"

// LeetCode problem description:
// https://leetcode.com/problems/path-with-maximum-probability/description/

class Solution {
public:
  double maxProbability(int n, vector<vector<int>> &edges,
                        vector<double> &succProb, int start_node,
                        int end_node) {
    // Create an adjacency list to represent the graph.
    vector<vector<pair<int, double>>> g(n);

    // Populate the adjacency list with edges and their probabilities.
    for (int i = 0; i < edges.size(); ++i) {
      g[edges[i][0]].push_back({edges[i][1], succProb[i]});
      g[edges[i][1]].push_back({edges[i][0], succProb[i]});
    }

    // Initialize an array to store maximum probabilities.
    vector<double> max_probabilities(n, 0.0);

    // Set the probability of the start_node to 1.0.
    max_probabilities[start_node] = 1.0;

    // Create a priority queue for efficient traversal.
    priority_queue<pair<double, int>> Q;

    // Push the starting node with probability 1.0 into the queue.
    Q.push({1.0, start_node});

    while (!Q.empty()) {
      // Get the edge with the maximum probability.
      pair<double, int> max_probability_edge = Q.top();
      Q.pop();

      // Get the current probability.
      double current_probabilty = max_probability_edge.first;

      // Get the current vertex.
      double current_vertex = max_probability_edge.second;

      // If we reach the end_node, return the maximum probability.
      if (current_vertex == end_node) {
        return current_probabilty;
      }

      // Iterate through the neighboring edges of the current_vertex.
      for (pair<int, double> &current_edge : g[current_vertex]) {
        // Update the maximum probability if a higher probability is found.
        if (max_probabilities[current_edge.first] <
            current_probabilty * current_edge.second) {
          max_probabilities[current_edge.first] =
              current_probabilty * current_edge.second;
          Q.push(
              {current_probabilty * current_edge.second, current_edge.first});
        }
      }
    }

    // Return 0.0 if no path is found from start_node to end_node.
    return 0.0;
  }
};

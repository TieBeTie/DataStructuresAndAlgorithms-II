#include "../../libs.hpp"

// LeetCode problem description:
// https://leetcode.com/problems/reconstruct-itinerary/description/

class Solution {
public:
  vector<string> findItinerary(vector<vector<string>> &tickets) {
    // Create a graph represented by a map of airports and multiset of
    // destinations.
    unordered_map<string, multiset<string>> m;

    // Populate the graph with tickets.
    for (auto &ticket : tickets) {
      m[ticket[0]].insert(ticket[1]);
    }

    // Initialize a deque to store the itinerary.
    deque<string> result;

    // Initialize a stack to perform DFS.
    stack<string> s;

    // Start the DFS from the "JFK" airport.
    s.emplace("JFK");

    while (!s.empty()) {
      // While there are no unexplored destinations from the current airport.
      while (m[s.top()].empty()) {
        // Add the airport to the front of the result deque.
        result.emplace_front(s.top());

        // Pop the airport from the stack.
        s.pop();

        // If the stack becomes empty, the DFS is complete.
        if (s.empty()) {
          // Return the reconstructed itinerary.
          return vector<string>(result.begin(), result.end());
        }
      }

      // Get the current airport.
      string &from = s.top();

      // Get the next destination.
      string to = *(m[from].begin());

      // Mark the destination as explored.
      m[from].erase(m[from].begin());

      // Push the destination onto the stack to continue the DFS.
      s.emplace(to);
    }

    // Return the reconstructed itinerary.
    return vector<string>(result.begin(), result.end());
  }
};

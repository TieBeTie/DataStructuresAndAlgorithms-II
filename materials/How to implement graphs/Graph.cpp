#include <iostream>
#include <vector>

using std::vector;

struct Nil {};

template <bool TOriented, class TEdge, bool TMatrix>
class Graph {};

template <>
class Graph<false, Nil, false> {
 public:
  Graph() {}
  Graph(size_t vertex_count) { graph.assign(vertex_count, vector<size_t>()); }
  Graph(size_t vertex_count, size_t edges_count) {
    graph.assign(vertex_count, vector<size_t>());
    this->edges_count = edges_count;
  }

  ~Graph() = default;

  void AddEdge(size_t head, size_t tail) {
    graph[head].push_back(tail);
    graph[tail].push_back(head);
    ++edges_count;
  }

  bool HasEdge(size_t head, size_t tail) {
    for (size_t i = 0; i < graph[head].size(); ++i) {
      if (graph[head][i] == tail) {
        return true;
      }
    }
    return false;
  }

  const vector<size_t> &GetNext(size_t parent) const { return graph[parent]; }

  size_t size() const { return graph.size(); }

  size_t EdgesCount() const { return edges_count; }

 private:
  vector<vector<size_t>> graph;
  size_t edges_count;
};

template <>
class Graph<true, Nil, false> {
 public:
  Graph() {}
  Graph(size_t vertex_count) { graph.assign(vertex_count, vector<size_t>()); }
  Graph(size_t vertex_count, size_t edges_count) {
    graph.assign(vertex_count, vector<size_t>());
    this->edges_count = edges_count;
  }

  ~Graph() = default;

  void AddEdge(size_t head, size_t tail) {
    graph[head].push_back(tail);
    ++edges_count;
  }

  bool HasEdge(size_t head, size_t tail) {
    for (size_t i = 0; i < graph[head].size(); ++i) {
      if (graph[head][i] == tail) {
        return true;
      }
    }
    return false;
  }

  const vector<size_t> &GetNext(size_t parent) const { return graph[parent]; }

  size_t size() const { return graph.size(); }

  size_t EdgesCount() const { return edges_count; }

 private:
  vector<vector<size_t>> graph;
  size_t edges_count;
};

template <class TEdge>
class Graph<true, TEdge, false> {
 public:
  Graph() {}
  Graph(size_t vertex_count) { graph.assign(vertex_count, vector<TEdge>()); }
  Graph(size_t vertex_count, size_t edges_count) {
    graph.assign(vertex_count, vector<TEdge>());
    this->edges_count = edges_count;
  }

  ~Graph() = default;

  void AddEdge(size_t head, TEdge edge) {
    graph[head].emplace(edge);
    ++edges_count;
  }

  bool HasEdge(size_t head, size_t tail) {
    for (size_t i = 0; i < graph[head].size(); ++i) {
      if (graph[head][i].tail == tail) {
        return true;
      }
    }
    return false;
  }

  const vector<TEdge> &GetNext(size_t parent) const { return graph[parent]; }

  size_t size() const { return graph.size(); }

  size_t EdgesCount() const { return edges_count; }

 private:
  vector<vector<TEdge>> graph;
  size_t edges_count;
};

int main() {
  struct Edge {
    size_t to;
    size_t weight;
  };
  Graph<true, Edge, false> graph;
}
#include <cstdio>
#include <vector>
#include <cstring>
#include <vector>
#include <queue>

class Network {
 public:
  Network(int n) : n_(n), graph_(n) {}

  void AddEdge(int from, int to, int capacity) {
    Edge e = {from, to, capacity};
    Edge re = {to, from, capacity};

    graph_[e.from].push_back(edges_.size());
    edges_.push_back(e);
    graph_[e.to].push_back(edges_.size());
    edges_.push_back(re);
  }

  long long MaxFlow(int s, int t) {
    long long flow = 0;
    while (true) {
      int delta = TryAugment(s, t);
      if (delta == 0) break;

      flow += delta;
    }

    return flow;
  }

 private:
  struct Edge { 
    Edge() : from(0), to(0), capacity(0), flow(0) {}
    Edge(int f, int t, int cap) : from(f), to(t), capacity(cap), flow(0) {}

    void DeltaCap(int delta) {
      capacity += delta;
    }

    bool CanIncrement() const {
      return flow < capacity;
    }

    int GetIncrement() const {
      return capacity - flow;
    }

    int from, to;
    int capacity, flow;
  };

  void IncrementFlow(int i, int delta) {
    edges_[i].flow += delta;
    edges_[i ^ 1].flow -= delta;
  }

  int TryAugment(int s, int t) {
    std::queue<int> q;
    std::vector<int> d(n_, -1), p(n_, -1);

    q.push(s);
    d[s] = kInf;

    while (!q.empty()) {
      int v = q.front(); q.pop();

      for (int i = 0; i < graph_[v].size(); ++i) {
        int edge_index = graph_[v][i];
        const Edge& e = edges_[edge_index];
        if (d[e.to] == -1 && e.CanIncrement()) {
          d[e.to] = std::min(d[v], e.GetIncrement());
          q.push(e.to);
          p[e.to] = edge_index;
        }
      }
    }

    if (d[t] <= 0) return 0;

    int curr = t, delta = d[t];
    while (p[curr] != -1) {
      IncrementFlow(p[curr], delta);
      curr = edges_[p[curr]].from;
    }

    return delta;
  }

  int n_;
  const int kInf = 1000000007;
  std::vector<Edge> edges_;
  std::vector<std::vector<int>> graph_;
};


constexpr int kMaxN = 35;


char table[kMaxN][kMaxN], replica[kMaxN][kMaxN];

int main() {
  int test_case; scanf("%d", &test_case);

  while (test_case-- > 0) {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%s", table[i]);

    std::vector<int> answer;
    for (int player = 0; player < n; ++player) {
      std::memcpy(replica, table, sizeof(table));

      int scored = 0;
      for (int i = 0; i < n; ++i) {
        if (replica[player][i] == '.') {
          scored += 2;
          replica[player][i] = '1';
          replica[i][player] = '0';
        } else if (replica[player][i] == '1') {
          scored += 2;
        } else if (replica[player][i] == 'd') {
          scored += 1;
        }
      }

      bool any = false;
      int games = 0;
      int sink = 10 + n + n * n;
      Network g(sink + 1);
      for (int i = 0; i < n; ++i) {
        if (i == player) continue;

        int current_score = 0;
        for (int j = 0; j < n; ++j) {
          if (replica[i][j] == '1') current_score += 2;
          else if (replica[i][j] == 'd') current_score += 1;
          else if (replica[i][j] == '.') games++;
        }

        if (current_score > scored) {
          any = true;
          break;
        }

        g.AddEdge(0, i + 1, scored - current_score);
      }

      if (any) continue;

      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          if (replica[i][j] == '.') {
            g.AddEdge(i + 1, i * n + j + n + 1, 2);
            g.AddEdge(j + 1, i * n + j + n + 1, 2);
            g.AddEdge(i * n + j + n + 1, sink, 2);
          }
        }
      }

      int flow = g.MaxFlow(0, sink);
      if (flow == games) printf("%d ", player + 1);
    }
    printf("\n");
  }

  return 0;
}

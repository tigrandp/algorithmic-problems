#include "../../../algorithms/graphs/unweighted_graph.h"
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  freopen("topsort.in", "r", stdin);
  freopen("topsort.out", "w", stdout);

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    UnweightedGraph g(n);

    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      g.AddEdge(u - 1, v - 1);
    }
    if (g.HasCycles()) {
      printf("-1\n");
    } else {
      std::vector<int> topsort = g.TopsortTraversal();
      for (int x : topsort) {
        printf("%d ", x + 1);
      }
      printf("\n");
    }
  }

  return 0;
}


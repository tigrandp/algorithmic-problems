#include <cstdio>
#include "../../../../algorithms/graphs/edmonds_karp_matrix.h"

int main() {
  int n, m; scanf("%d%d", &n, &m);

  Network g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, c; scanf("%d%d", &u, &v);
    g.AddEdge(u - 1, v - 1, 1);
  }

  int source = 0, answer = m;
  for (int sink = 1; sink < n; ++sink) {
    Network g_c(g);
    answer = std::min(answer, (int)g_c.MaxFlow(source, sink));
  }

  printf("%d\n", answer);

  return 0;
}

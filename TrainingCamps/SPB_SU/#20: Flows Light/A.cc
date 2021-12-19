#include <cstdio>
#include "../../../../algorithms/graphs/edmonds_karp_matrix.h"

int main() {
  int n, m; scanf("%d%d", &n, &m);

  Network g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    g.AddEdge(u - 1, v - 1, c);
  }

  printf("%lld\n", g.MaxFlow(0, n - 1));

  return 0;
}

#include <algorithm>
#include <cstdio>
#include <vector>

constexpr int kMaxN = 20010;

int n, m, c[kMaxN], comp[kMaxN], comp_in[kMaxN], comp_out[kMaxN];
std::vector<int> g[kMaxN];

void Dfs(int v, int comp_id) {
  comp[v] = comp_id;

  if (v < n) comp_in[comp_id] += c[v];
  else comp_out[comp_id] += c[v];

  for (int u : g[v]) {
    if (comp[u]) continue;
    Dfs(u, comp_id);
  }
}

int main() {
  scanf("%d%d", &n, &m);

  // Read data and construct the graph.
  for (int i = 0; i < n; ++i) scanf("%d", c + i);
  for (int i = 0; i < n; ++i) scanf("%d", c + n + i);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v); --u; --v;
    g[u].push_back(v + n);
    g[v + n].push_back(u);
  }

  // Find connected components and for each component
  // calcuate how much flow we received and how much can
  // be sent out.
  int comp_id = 1;
  for (int i = 0; i < n; ++i) {
    if (comp[i]) continue;
    Dfs(i, comp_id); comp_id++;
  }

  // Calculate the flow as the min between how much we received and how
  // much we can send out.
  long long flow = 0;
  for (int i = 0; i < comp_id; ++i) flow += std::min(comp_in[i], comp_out[i]);
  printf("%lld\n", flow);
 
  return 0;
}

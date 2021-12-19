#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <utility>
#include <set>

int main() {
  freopen("inevit.in", "r", stdin);
  freopen("inevit.out", "w", stdout);

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    UnweightedGraph g(n);

    std::map<std::pair<int, int>, int> edges;

    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      g.AddEdge(u - 1, v - 1);
      g.AddEdge(v - 1, u - 1);
      edges[std::make_pair(u - 1, v - 1)] = i;
      edges[std::make_pair(v - 1, u - 1)] = i;
    }

    std::vector<int> path = g.ShortestPath(0, n - 1);
    assert(!path.empty());

    std::set<int> edge_numbers;
    for (int i = 0; i + 1 < path.size(); ++i) {
      edge_numbers.insert(edges[std::make_pair(path[i], path[i + 1])]);
    }

    std::vector<int> answer;
    std::vector<std::pair<int, int>> bridges = g.FindBridges();
    for (const auto& b : bridges) {
      if (edge_numbers.count(edges[b])) {
        answer.push_back(edges[b] + 1);
      }
    }

    printf("%d\n", answer.size());
    std::sort(answer.begin(), answer.end());
    for (int x : answer) {
      printf("%d ", x);
    }
    printf("\n");
  }

  return 0;
}


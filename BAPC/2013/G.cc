#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>

constexpr int kMaxN = 1111;

int n;
double kEps = 1e-8;
double x[kMaxN], y[kMaxN], r[kMaxN];

char was[kMaxN];
std::vector<int> g[kMaxN];

void Dfs(int v) {
  was[v] = true;
  for (int to : g[v])
    if (!was[to])
      Dfs(to);
}

bool Can(double lb, double rb) {
  int lb_num = n, rb_num = n + 1;

  g[n].resize(0);
  g[n + 1].resize(0);
  for (int i = 0; i < n; ++i) {
    g[i].resize(0);
    // Edge (lb_num, i)
    if (fabs(x[i] - lb) + kEps <= r[i]) {
      g[lb_num].push_back(i);
      g[i].push_back(lb_num);

      //fprintf(stderr, "Edge (%d, %d)\n", lb_num, i);
    }

    // Edge (rb_num, i)
    if (fabs(x[i] - rb) + kEps <= r[i]) {
      g[rb_num].push_back(i);
      g[i].push_back(rb_num);

      //fprintf(stderr, "Edge (%d, %d)\n", rb_num, i);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double d = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
      if (d + kEps < (r[i] + r[j]) * (r[i] + r[j])) {
        g[i].push_back(j);
        g[j].push_back(i);

        //fprintf(stderr, "Edge (%d, %d)\n", i, j);
      }
    }
  }

  std::memset(was, 0, sizeof(was));
  Dfs(lb_num);

  return !was[rb_num];
}

int main() {
  int test_case; scanf("%d", &test_case);
  while (test_case--) {
    double w; scanf("%lf%d", &w, &n);
    for (int i = 0; i < n; ++i) {
      scanf("%lf%lf%lf", x + i, y + i, r + i);
    }

    double low = 0.0, high = w * 0.5, res = 0.0;
    for (int it = 0; it < 100; ++it) {
      double mid = (low + high) * 0.5;
      for (int i = 0; i < n; ++i) r[i] += mid;

      if (Can(mid, w - mid)) {
        res = mid;
        low = mid;
      } else {
        high = mid;
      }

      for (int i = 0; i < n; ++i) r[i] -= mid;
    }

    printf("%.7lf\n", res);
  }

  return 0;
}

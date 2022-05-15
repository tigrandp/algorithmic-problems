#include <cstdio>
#include <cstring>
#include <algorithm>

int n, b[16];
double dp[1 << 16][17], p[16];

double Solve(int mask, int cnt, int money) {
  if (cnt == 0) return 1.0;

  double& ret = dp[mask][cnt];
  if (ret > -0.5) return ret;

  ret = 0.0;
  for (int i = 0; i < n; ++i) {
    if (mask & (1 << i)) continue;
    if (b[i] > money) continue;

    ret = std::max(ret, Solve(mask | (1 << i), cnt - 1, money - b[i]) * p[i] + Solve(mask | (1 << i), cnt, money - b[i]) * (1 - p[i]));
  }
  return ret;

}

int main() {
  int t; scanf("%d", &t);
  while (t--) {
    int c, m;
    scanf("%d%d%d", &n, &c, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%d%lf", b + i, p + i);
      p[i] /= 100.0;
    }

    std::memset(dp, -1, sizeof(dp));
    printf("%.8lf\n", Solve(0, c, m));
  }

  return 0;
}

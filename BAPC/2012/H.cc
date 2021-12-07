#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>

constexpr int kInf = 5000;
constexpr int kMaxN = 1010;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int d[kMaxN][kMaxN], lm[kMaxN], rm[kMaxN];

int main() {
  int t; scanf("%d", &t);

  while (t-- > 0) {
    int k, m, n;
    scanf("%d%d%d", &k, &m, &n);
    std::memset(d, 63, sizeof(d));

    std::queue<std::pair<int, int>> q;
    for (int i = 0; i < k; ++i) {
      int x, y;
      scanf("%d%d", &y, &x);
      d[x][y] = 0;
      q.push({x, y});
    }

    while (!q.empty()) {
      int x = q.front().first;
      int y = q.front().second;
      q.pop();

      for (int k = 0; k < 4; ++k) {
        int n_x = x + dx[k];
        int n_y = y + dy[k];

        if (n_x < 0 || n_y < 0) continue;
        if (n_x >= n || n_y >= m) continue;
        if (d[n_x][n_y] < kInf) continue;

        d[n_x][n_y] = d[x][y] + 1;
        q.push({n_x, n_y});
      }
    }

    int lo = 1, hi = kInf, res = -1;
    while (lo <= hi) {
      int x = (lo + hi) / 2;

      std::memset(lm, -1, sizeof(lm));
      std::memset(rm, -1, sizeof(rm));
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          if (d[i][j] >= x) {
            lm[i] = j;
            break;
          }
        }
        for (int j = m - 1; j >= 0; --j) {
          if (d[i][j] >= x) {
            rm[i] = j;
            break;
          }
        }
      }

        bool found = false;
        for (int i = 0; i < n && !found; ++i) {
          for (int j = 0; j < n && !found; ++j) {
            if (lm[i] != -1 && rm[j] != -1) {
              // (i, lm[i]) --> (j, rm[j])
              int dist = std::abs(i - j) + std::abs(lm[i] - rm[j]);
              if (dist >= x) {
                found = true;
              }
            }
          }
        }

        if (found) {
          res = x;
          lo = x + 1;
        } else {
          hi = x - 1;
        }
    }
    printf("%d\n", res);
  }
  return 0;
}

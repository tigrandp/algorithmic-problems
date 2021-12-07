#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>

constexpr int kMaxN = 1010;

int n, m, d[kMaxN][kMaxN];
char a[kMaxN][kMaxN], buffer[kMaxN];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
//  freopen("input.txt", "r", stdin);

  int t; scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &m, &n);
    std::memset(a, 0, sizeof(a));
    std::memset(d, -1, sizeof(d));
    std::queue<std::tuple<int, int, char>> q;
    for (int i = 0; i < n; ++i) {
      scanf("%s", &buffer);
      for (int j = 0; j < m; ++j) {
        a[i][j] = buffer[j];
        if (a[i][j] == '@') {
          d[i][j] = 0;
          q.push(std::make_tuple(i, j, a[i][j]));
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (a[i][j] == '*') {
          d[i][j] = 0;
          q.push(std::make_tuple(i, j, a[i][j]));
        }
      }
    }

    bool escaped = false;
    while (!q.empty()) {
      auto e = q.front();
      q.pop();

      int x = std::get<0>(e);
      int y = std::get<1>(e);
      char ch = std::get<2>(e);

      if (ch == '@' && a[x][y] == '*') continue;

      for (int k = 0; k < 4; ++k) {
        int n_x = x + dx[k];
        int n_y = y + dy[k];

        if (ch == '@') {
          if (n_x == -1 || n_y == -1 || n_x == n || n_y == m) {
            escaped = true;
            printf("%d\n", d[x][y] + 1);
            break;
          }
        }
        if (n_x >= 0 && n_y >= 0 && n_x < n && n_y < m) {
          if (ch == '@' && d[n_x][n_y] != -1) continue;
          if (a[n_x][n_y] == '#') continue;
          if (a[n_x][n_y] == '*') continue;

          d[n_x][n_y] = d[x][y] + 1;
          a[n_x][n_y] = ch;
          q.push(std::make_tuple(n_x, n_y, ch));
        }
      }

      if (escaped) break;
    }
    if (!escaped) {
      printf("IMPOSSIBLE\n");
    }
  }

  return 0;
}

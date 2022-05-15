#include <cstdio>
#include <vector>
#include <deque>
#include <utility>

constexpr int kMaxN = 111;

int n, m;
char a[kMaxN][kMaxN];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool IsValid(int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m;
}

void Bfs(const std::vector<std::pair<int, int>>& s,
         std::vector<std::vector<int>>& d) {
  std::deque<std::pair<int, int>> q;
  for (const auto& e : s) q.push_back(e);

  while (!q.empty()) {
    std::pair<int, int> t = q.front();
    q.pop_front();

    int x = t.first;
    int y = t.second;

    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k];
      int ny = y + dy[k];

      if (IsValid(nx, ny) && a[nx][ny] != '*' && d[nx][ny] == -1 && (a[nx][ny] == '.' || a[nx][ny] == '$')) {
        q.push_front({nx, ny});
        d[nx][ny] = d[x][y];
      }
    }

    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k];
      int ny = y + dy[k];

      if (IsValid(nx, ny) && a[nx][ny] != '*' && d[nx][ny] == -1 && a[nx][ny] == '#') {
        q.push_back({nx, ny});
        d[nx][ny] = d[x][y] + 1;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      fprintf(stderr, "%d\t", d[i][j]);
    }
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "\n");
}

int main() {
  int t; scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%s", a[i]);

    std::vector<std::vector<int>> d_border(n, std::vector<int>(m, -1)),
                                  d_first(n, std::vector<int>(m, -1)),
                                  d_second(n, std::vector<int>(m, -1));

    std::vector<std::pair<int, int>> border, first, second;
    // At first push the empty spaces.
    for (int i = 0; i < n; ++i) {
      if (a[i][0] == '.') {
        border.emplace_back(i, 0);
        d_border[i][0] = 0;
      }
      if (a[i][m - 1] == '.') {
        border.emplace_back(i, m - 1);
        d_border[i][m - 1] = 0;
      }
    }
    for (int i = 0; i < m; ++i) {
      if (a[0][i] == '.') {
        border.emplace_back(0, i);
        d_border[0][i] = 0;
      }
      if (a[n - 1][i] == '.') {
        border.emplace_back(n - 1, i);
        d_border[n - 1][i] = 0;
      }
    }

    // And only then the walls.
    for (int i = 0; i < n; ++i) {
      if (a[i][0] == '#') {
        border.emplace_back(i, 0);
        d_border[i][0] = 1;
      }
      if (a[i][m - 1] == '#') {
        border.emplace_back(i, m - 1);
        d_border[i][m - 1] = 1;
      }
    }
    for (int i = 0; i < m; ++i) {
      if (a[0][i] == '#') {
        border.emplace_back(0, i);
        d_border[0][i] = 1;
      }
      if (a[n - 1][i] == '#') {
        border.emplace_back(n - 1, i);
        d_border[n - 1][i] = 1;
      }
    }

    // Find the prisoners positions.
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (a[i][j] == '$') {
          if (first.empty()) {
            first.emplace_back(i, j);
            d_first[i][j] = 0;
          }
          else {
            second.emplace_back(i, j);
            d_second[i][j] = 0;
          }
        }
      }
    }

    fprintf(stderr, "Border:\n");
    Bfs(border, d_border);

    fprintf(stderr, "First:\n");
    Bfs(first, d_first);
    
    fprintf(stderr, "Second:\n");
    Bfs(second, d_second);

    constexpr int kInf = 1000000;
    int answer = kInf;
    int mmin1 = kInf, mmin2 = kInf;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
          if (d_first[i][j] != -1) mmin1 = std::min(mmin1, d_first[i][j]);
          if (d_second[i][j] != -1) mmin2 = std::min(mmin2, d_second[i][j]);
        }
        if (d_border[i][j] != -1 && d_first[i][j] != -1 && d_second[i][j] != -1) {
          int z = a[i][j] == '#' ? 1 : 0;
          answer = std::min(answer, d_border[i][j] + d_first[i][j] + d_second[i][j] - 2 * z);
        }
      }
    }

    printf("%d\n", std::min(mmin1 + mmin2, answer));
  }

  return 0;
}

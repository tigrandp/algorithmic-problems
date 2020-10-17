#include <cstdio>
#include <cstring>
#include <queue>

constexpr int kMaxN = 66;
constexpr int kMaxP = 205;

int sx, sy, fx, fy;
int n, m, p, l[kMaxP];
char a[kMaxN][kMaxN];
int mx[205][10];
int my[205][10];
bool u[125][kMaxN][kMaxN];
int d[kMaxN][kMaxN][125];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int Gcd(int a, int b) {
  if (b == 0) return a;
  return Gcd(b, a % b);
}

int Lcm(int a, int b) {
  return a * b / Gcd(a, b);
}

struct State {
  int x;
  int y;
  int t;
};

int Bfs(int x0, int y0, int x1, int y1, int mt) {
  std::queue<State> q;
  q.push({x0, y0, 0});
  d[x0][y0][0] = 0;
  while (!q.empty()) {
    State s = q.front();
    q.pop();

    for (int td = 0; td <= mt; ++td) {
      int new_t = (s.t + td) % mt;
      if (!u[new_t][s.x][s.y] && d[s.x][s.y][new_t] == -1) {
        d[s.x][s.y][new_t] = d[s.x][s.y][s.t] + td;
        q.push({s.x, s.y, new_t});
      }
    }

    for (int k = 0; k < 4; ++k) {
      int nx = s.x + dx[k];
      int ny = s.y + dy[k];

      if (nx < 0 || nx >= n) continue;
      if (ny < 0 || ny >= m) continue;
      if (a[nx][ny] == '#') continue;
      if (nx == x1 && ny == y1) return d[s.x][s.y][s.t] + 1;

      int new_t = (d[s.x][s.y][s.t] + 1) % mt;
      if (u[new_t][nx][ny]) continue;
      if (d[nx][ny][new_t] != -1) continue;

      d[nx][ny][new_t] = d[s.x][s.y][s.t] + 1;
      q.push({nx, ny, new_t});
    }
  }
  return -1;
}

int main() {
  char tmp;
  scanf("%d%d", &n, &m);
  scanf(" %c%d%d%c %c%d%d%c", &tmp, &sx, &sy, &tmp, &tmp, &fx, &fy, &tmp);
  for (int i = 0; i < n; ++i) scanf("%s", a[i]);
  scanf("%d", &p);

  int lcm = 1;
  for (int i = 0; i < p; ++i) {
    scanf("%d", l + i);
    if (l[i] > 1) lcm = Lcm(lcm, 2 * (l[i] - 1));
    for (int j = 0; j < l[i]; ++j) {
      scanf(" %c%d%d%c", &tmp, mx[i] + j, my[i] + j, &tmp);
      --mx[i][j]; --my[i][j];
    }
  }

  // printf("LCM=%d\n", lcm);

  // Position of every teacher at time t.
  for (int t = 0; t <= lcm; ++t) {
    // printf("At time T=%d under attack: ", t);
    for (int i = 0; i < p; ++i) {
      int ind = 0;
      if (l[i] > 1) {
        int z = t / (l[i] - 1);
        if (z & 1) ind = l[i] - 1 - t % (l[i] - 1);
        else ind = t % (l[i] - 1);
      }
      // printf("%d ", ind);
      for (int k = 0; mx[i][ind] - k >= 0; ++k) {
        if (a[mx[i][ind] - k][my[i][ind]] == '#') break;
        // printf("(%d %d) ", mx[i][ind] - k, my[i][ind]);
        u[t][mx[i][ind] - k][my[i][ind]] = true;
      }
      for (int k = 0; mx[i][ind] + k < n; ++k) {
        if (a[mx[i][ind] + k][my[i][ind]] == '#') break;
        // printf("(%d %d) ", mx[i][ind] + k, my[i][ind]);
        u[t][mx[i][ind] + k][my[i][ind]] = true;
      }
      for (int k = 0; my[i][ind] - k >= 0; ++k) {
        if (a[mx[i][ind]][my[i][ind] - k] == '#') break;
        // printf("(%d %d) ", mx[i][ind], my[i][ind] - k);
        u[t][mx[i][ind]][my[i][ind] - k] = true;
      }
      for (int k = 0; my[i][ind] + k < m; ++k) {
        if (a[mx[i][ind]][my[i][ind] + k] == '#') break;
        // printf("(%d %d) ", mx[i][ind], my[i][ind] + k);
        u[t][mx[i][ind]][my[i][ind] + k] = true;
      }
      // printf("\n");
    }
  }
  memset(d, -1, sizeof(d));
  int res = Bfs(sx - 1, sy - 1, fx - 1, fy - 1, lcm);
  if (res == -1) printf("IMPOSSIBLE\n");
  else printf("%d\n", res);
  return 0;
}

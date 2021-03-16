#include <cstdio>
#include <cstring>

constexpr int kMaxN = 22;
constexpr int kMaxM = 111;

int n, c[kMaxN], m, k[kMaxM], p[kMaxM], a[kMaxM][kMaxN];

int main() {
  while (scanf("%d", &n) == 1) {
    memset(c, 0, sizeof(c));
    memset(k, 0, sizeof(k));
    memset(a, 0, sizeof(a));
    memset(p, 0, sizeof(p));

    int s = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", c + i);
      s += c[i];
    }

    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
      scanf("%d", k + i);
      for (int j = 0; j < k[i]; ++j) {
        scanf("%d", a[i] + j); --a[i][j];
        p[i] |= 1 << a[i][j];
      }
    }

    int res = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
      bool ok = true;
      int combined = 0;
      for (int j = 0; j < m; ++j) {
        if ((mask & p[j]) == 0) {
          ok = false;
        }
        combined |= mask & p[j];
      }

      if (ok) {
        int answer = s;
        // fprintf(stderr, "Mask=%d Combined=%d\n", mask, combined);
        for (int j = 0; j < n; ++j) {
          if (combined & (1 << j)) answer -= c[j];
        }
        if (res < answer) res = answer;
      }
    }

    printf("%d\n", res);
  }

  return 0;
}

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  freopen("right.in", "r", stdin);
  freopen("right.out", "w", stdout);

  int n, m;
  scanf("%d%d", &n, &m);

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int q = 0; q < m; ++q) {
    int x;
    scanf("%d", &x);

    int lo = 0, hi = n - 1, res = -1;

    while (lo <= hi) {
      int mid = (lo + hi) / 2;

      if (a[mid] > x) {
        hi = mid - 1;
      } else {
        if (a[mid] == x) {
          res = mid;
        }
        lo = mid + 1;
      }
    }

    printf("%d\n", res + 1);
  }

  return 0;
}


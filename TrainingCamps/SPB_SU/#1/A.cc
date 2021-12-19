#include <cstdio>

int main() {
  freopen("absum.in", "r", stdin);
  freopen("absum.out", "w", stdout);

  long long a, b;
  while (scanf("%lld%lld", &a, &b) == 2) {
    printf("%lld\n", a + b);
  }

  return 0;
}

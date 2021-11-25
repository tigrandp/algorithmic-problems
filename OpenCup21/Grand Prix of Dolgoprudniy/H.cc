#include <algorithm>
#include <iostream>

long long Solve(long long u, long long v, long long n) {
  int steps = 0;
  while (v > u && v >= 1 && u >= 1) {
    long long rem = n % v;
    if (rem == 0) return -1;

    steps++;
    v -= rem;

    if (u > v) std::swap(u, v);
  }

  return v == u ? steps : -1;
}

int main() {
  int t; scanf("%lld", &t);

  while (t-- > 0) {
    long long n, u, v; scanf("%lld%lld%lld", &n, &u, &v);
    printf("%lld\n", Solve(std::min(u, v), std::max(u, v), n));
  }

  return 0;
}

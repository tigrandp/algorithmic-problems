#include <algorithm>
#include <cstdio>
#include <vector>

constexpr int kMod = 1743;

int buckets[kMod + 1];

void Poly(int x) {
  x %= kMod;
  int ret = (132 * (((x * x) % kMod * x) % kMod) +
             77 * x * x +
             1345 * x + 1577) % kMod;
  buckets[ret]++;
}

int main() {
  freopen("kth.in", "r", stdin);
  freopen("kth.out", "w", stdout);

  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    Poly(i + 1);
  }
  for (int i = 0; i < kMod; ++i) {
    if (buckets[i] < k) k -= buckets[i];
    else if (buckets[i] >= k) {
      printf("%d\n", i);
      break;
    }
  }

  return 0;
}


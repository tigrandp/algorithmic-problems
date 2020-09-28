#include <cstdio>
#include <set>

constexpr int kMaxN = 1100;
constexpr long double kEps = 1e-9;

int n, m;
long long t[kMaxN], d[kMaxN];

struct DoubleCmp {
  bool operator() (long double lhs, long double rhs) const {
    return lhs + kEps < rhs;
  }
};

int main() {
  while (scanf("%d%d", &m, &n) == 2) {
    for (int i = 0; i < m; ++i) scanf("%lld", t + i);
    for (int i = 0; i < n; ++i) scanf("%lld", d + i);

    std::set<long double> v;
    std::set<long long> z;
    for (int i = 0; i + m <= n; ++i) {
      std::set<long double, DoubleCmp> speeds;
      for (int j = i; j + 2 <= i + m; ++j) {
        long double delta_t = t[j - i + 1] - t[j - i];
        long double delta_d = d[j + 1] - d[j];
        long double speed = delta_d / delta_t;
        speeds.insert(speed);
      }
      if (speeds.size() == 1) {
        v.insert(*speeds.begin());
        z.insert(d[i + 1] - d[i]);
      }
    }

    printf("%d\n", v.size());
    for (long long x : z) printf("%lld ", x);
    printf("\n");
  }

  return 0;
}

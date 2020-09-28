#include <cmath>
#include <cstdio>
#include <vector>

int main() {
  int n;
  double g;

  double pi = std::acos(-1.0);
  while (scanf("%d%lf", &n, &g) == 2) {
    std::vector<double> ds(n), thetta(n);
    for (int i = 0; i < n; ++i) {
      scanf("%lf%lf", &ds[i], &thetta[i]);
    }
    for (int i = 0; i < n; ++i) {
      double v = 0.0;
      for (int j = i; j < n; ++j) {
        double a = g * std::cos(thetta[j] * pi / 180.0);
        double t = (std::sqrt(v * v + 2 * a * ds[j]) - v) / a;
        v += t * a;
      }
      printf("%.7lf\n", v);
    }
  }

  return 0;
}

#include <cmath>
#include <cstdio>
#include <vector>

constexpr int kMaxN = 200010;
constexpr double Pi = std::acos(-1.0);
constexpr double kEps = 1e-9;

int n, x[kMaxN], y[kMaxN], l[kMaxN], r[kMaxN];

long long DeltaY(int i, int j) {
  return std::abs(y[i] - y[j]);
}

long long DeltaX(int i, int j) {
  return std::abs(x[i] - x[j]);
}

bool BetterSlope(int i, int j, int k) {
  return DeltaY(i, j) * DeltaX(i, k) >= DeltaY(i, k) * DeltaX(i, j);
}

void CalculateFromLeft() {
  std::vector<int> s = {0};
  l[0] = -1;

  for (int i = 1; i < n; ++i) {
    while (!s.empty() && y[s.back()] <= y[i]) s.pop_back();
    while (s.size() > 1 && BetterSlope(i, s[s.size() - 2], s[s.size() - 1])) s.pop_back();
    l[i] = s.empty() ? -1 : s.back();
    s.push_back(i);
  }
}

void CalculateFromRight() {
  std::vector<int> s = {n - 1};
  r[n - 1] = -1;

  for (int i = n - 2; i >= 0; --i) {
    while (!s.empty() && y[s.back()] <= y[i]) s.pop_back();
    while (s.size() > 1 && BetterSlope(i, s[s.size() - 2], s[s.size() - 1])) s.pop_back();
    r[i] = s.empty() ? -1 : s.back();
    s.push_back(i);
  }
}

double GetAngle(int i, int j) {
  return std::atan(DeltaY(i, j) * 1.0 / DeltaX(i, j));
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", x + i, y + i);
  }
  CalculateFromLeft();
  CalculateFromRight();

  for (int i = 0; i < n; ++i) {
    double p = Pi;
    if (l[i] != -1) p -= GetAngle(i, l[i]);
    if (r[i] != -1) p -= GetAngle(i, r[i]);
    printf("%.8lf\n", 12.0 * p / Pi);
  }

  return 0;
}

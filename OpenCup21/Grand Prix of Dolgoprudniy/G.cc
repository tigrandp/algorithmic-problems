#include <algorithm>
#include <cstdio>
#include <set>
#include <unordered_map>
#include <vector>

constexpr int kMaxN = 400007;

std::unordered_map<int, int> r;
std::unordered_map<int, int> rev;
int n, rank = 1, A[kMaxN], B[kMaxN], X[kMaxN];
long long sumA[kMaxN], sumB[kMaxN];

double TotalProfit(double p_a, int a, int b) {
  double p_b = 0.25 * (sumA[b] + sumB[b]) -
               0.25 * (sumA[rank] - sumA[b]) -
               0.25 * (sumB[rank] - sumB[b]);

  double ret = p_a + p_b - (long long)a * rev[b];
  return ret;
}

int main() {
  // freopen("input.txt", "r", stdin);

  scanf("%d", &n);
  std::set<int> s;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", A + i, B + i, X + i);
    s.insert(A[i]);
    s.insert(B[i]);
  }
  s.insert(1);

  for (int x : s) {
    if (!r.count(x)) {
      r[x] = rank;
      rev[rank] = x;
      rank++;
    }
  }

  for (int i = 0; i < n; ++i) {
    sumA[r[A[i]]] += X[i];
    sumB[r[B[i]]] += X[i];
  }

  for (int i = 1; i <= rank; ++i) {
    sumA[i] += sumA[i - 1];
    sumB[i] += sumB[i - 1];
  }

  std::vector<int> z(s.begin(), s.end());
  double res = -1.0 * (1e16);
  // Consider all possible first value, where first value <= second value.
  for (int i = 0; i < z.size(); ++i) {
    int a = z[i];
    double profit_a = 0.5 * (sumA[r[a]] + sumB[r[a]]) - 0.25 * (sumA[rank] + sumB[rank]);
    int from = std::max(i, i - 50);
    int to = std::min((int)z.size() - 1, i + 50);
    for (int i = from; i <= to; ++i) {
      res = std::max(res, TotalProfit(profit_a, a, z[i]));
    }
  }

  printf("%.8lf\n", res);

  return 0;
}

#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>

int N, NUM_DICE = 8;
double f[9][1 << 7][44], prob[9][9][9][9][9][9][9];
double answers[] = {0.993426098, 0.993426098, 0.993426098, 0.993426098, 0.993426098, 0.993424769, 0.993416597, 0.993400282, 0.993362460, 0.993267327, 0.993022984, 0.992575739, 0.991724368, 0.989860616, 0.986007956, 0.981013031, 0.972551376, 0.959825570, 0.942153397, 0.918872284, 0.893026737, 0.855601586, 0.807738507, 0.748373334, 0.680330711, 0.606990190, 0.524759447, 0.435420465, 0.346293287, 0.263789519, 0.194014936, 0.135812521, 0.086775216, 0.052617594, 0.028907505, 0.015678145, 0.007502412, 0.002685522, 0.000955855, 0.000146108};

void Precalc(std::vector<int> v, int nn) {
  if (v.size() == nn) {
    std::vector<int> c(7);
    for (int x : v) c[x]++;
    prob[nn][c[1]][c[2]][c[3]][c[4]][c[5]][c[6]] += std::pow(1.0 / 6.0, nn);
    return;
  }
  for (int d = 1; d <= 6; ++d) {
    v.push_back(d);
    Precalc(v, nn);
    v.pop_back();
  }
}



double Solve(int n, int mask, int sum) {
  if (sum >= N) {
    if (mask & (1 << 6)) {
      return 1.0;
    }
  }
  if (n == 0) {
    return 0.0;
  }

  double& ref = f[n][mask][sum];
  if (ref > -0.5) return ref;
  ref = 0.0;

  for (int c1 = 0; c1 <= n; ++c1) {
    for (int c2 = 0; c2 <= n - c1; ++c2) {
      for (int c3 = 0; c3 <= n - c1 - c2; ++c3) {
        for (int c4 = 0; c4 <= n - c1 - c2 - c3; ++c4) {
          for (int c5 = 0; c5 <= n - c1 - c2 - c3 - c4; ++c5) {
            for (int c6 = 0; c6 <= n - c1 - c2 - c3 - c4 - c5; ++c6) {
              if (c1 + c2 + c3 + c4 + c5 + c6 != n) continue;
              double mmax = 0.0;
              std::vector<int> v = {0, c1, c2, c3, c4, c5, c6};
              for (int d = 1; d <= 6; ++d) {
                if (mask & (1 << d)) continue;
                if (v[d] <= 0) continue;
                int vl = d;
                if (d == 6) vl = 5;
                mmax = std::max(mmax, prob[n][c1][c2][c3][c4][c5][c6] * Solve(n - v[d], mask ^ (1 << d), std::min(N, sum + v[d] * vl)));
              }
              ref += mmax;
            }
          }
        }
      }
    }
  }

  return ref;
}

int main() {
  int t; scanf("%d", &t);
  while (t-- > 0) {
    int rn; scanf("%d", &rn);
    printf("%.9lf\n", answers[rn - 1]);
  }
//  for (int i = 1; i <= NUM_DICE; ++i) Precalc({}, i);
//  printf("[");
//  for (N = 1; N <= 40; ++N) {
//    for (int n = 0; n <= 8; ++n) {
//      for (int mask = 0; mask < (1 << 7); ++mask) {
//        for (int sum = 0; sum <= N; ++sum) {
//          f[n][mask][sum] = -1.0;
//        }
//      }
//    }
//    printf("%.9lf, ", Solve(NUM_DICE, 0, 0));
//  }
//  printf("]");

  return 0;
}

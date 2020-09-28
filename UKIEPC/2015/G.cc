#include <iostream>
#include <map>

int n;
std::string names[10];
int d[10], c[10];

bool was[1010][150];
bool can[1010][150];

std::map<std::string, int> cnt;

bool Can(int money, int units) {
  if (money == 0 && units == 0) return true;
  if (was[money][units]) return can[money][units];
  was[money][units] = true;
  bool& ref = can[money][units];
  ref = false;

  for (int i = 0; i < n && !ref; ++i) {
    if (c[i] == 0 && d[i] == 0) continue;
    if (c[i] <= money && d[i] <= units) {
      ref |= Can(money - c[i], units - d[i]);
    }
  }
  
  return ref;
}

void Construct(int money, int units) {
  if (money == 0 &&  units == 0) return;
  for (int i = 0; i < n; ++i) {
    if (c[i] == 0 && d[i] == 0) continue;
    if (c[i] <= money && d[i] <= units) {
      if (Can(money - c[i], units - d[i])) {
        cnt[names[i]]++;
        Construct(money - c[i], units - d[i]);
        return;
      }
    }
  }
}

int main() {
  int D;
  double M, U;
  std::cin >> M >> U >> D;

  n = D;
  int m = M * 100.0;
  U *= 6.0;
  if (U - static_cast<int>(U) > 1e-9) {
    std::cout << "IMPOSSIBLE";
    return 0;
  }
  int u = U;

  for (int i = 0; i < n; ++i) {
    std::cin >> names[i];
    int x; std::cin >> x;
    int part;
    char ch;
    int tmp;
    scanf("%d%c%d", &tmp, &ch, &part);
    d[i] = (6 / part) * x;
    double z;
    scanf("%lf\n", &z);
    c[i] = z * 100.0;
  }

  bool res = Can(m, u);
  if (!res) {
    std::cout << "IMPOSSIBLE";
    return 0;
  }

  Construct(m, u);
  for (const auto& e : cnt) {
    std::cout << e.first << " " << e.second << std::endl;
  }

  return 0;
}


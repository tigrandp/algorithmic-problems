#include <string>
#include <iostream>
#include <map>

int main() {
  int t; scanf("%d", &t);
  while (t--) {
    int n; scanf("%d", &n);

    std::map<std::string, int> cnt;
    for (int i = 0; i < n; ++i) {
      std::string name, cat;
      std::cin >> name >> cat;
      cnt[cat]++;
    }

    long long answer = 1;
    for (const auto& e : cnt) {
      answer *= e.second + 1;
    }
    std::cout << answer - 1 << std::endl;
  }

  return 0;
}

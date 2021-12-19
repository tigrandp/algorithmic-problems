#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <utility>
#include <set>
#include <cstring>
#include <unordered_map>

char s[2002];

struct Link {
  std::map<int, Link*> links;
};

int main() {
  freopen("bacon.in", "r", stdin);
  freopen("bacon.out", "w", stdout);

  while (scanf("%s", &s) == 1) {
    int answer = 0;
    int n = strlen(s);
    Link* root = new Link();
    for (int i = 0; i < n; ++i) {
      Link* current = root;
      for (int j = i; j < n; ++j) {
        if (current->links[s[j]] == nullptr) {
          current->links[s[j]] = new Link();
          ++answer;
        }
        current = current->links[s[j]];
      }
    }
    printf("%d\n", answer);
  }

  return 0;
}


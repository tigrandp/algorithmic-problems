#include <cstdio>
#include <cstring>
#include <string>

constexpr int kMaxN = 10010;

char s[kMaxN];
char hard[] = "bcdgknpt";

bool IsHard(char ch) {
  ch = tolower(ch);
  for (int i = 0; i < 8; ++i) {
    if (hard[i] == ch) return true;
  }
  return false;
}

char ClosestHard(char ch, bool is_upper) {
  int i = -1;
  if (is_upper) ch = tolower(ch);
  for (int j = 0; j < 8; ++j) {
    if (i == -1 || std::abs(ch - hard[j]) < std::abs(ch - hard[i]))
      i = j;
  }
  if (is_upper) return toupper(hard[i]);
  return hard[i];
}

std::string GetEnding(char ch) {
  ch = tolower(ch);
  static char v[] = "aou";
  int i = -1;
  for (int j = 0; j < 3; ++j)
    if (i == -1 || std::abs(ch - v[j]) < std::abs(ch - v[i]))
      i = j;
  return std::string(1, v[i]) + "h";
}

std::string Transform(const std::string& s) {
  std::string t;
  t.reserve(s.size());
  if (!IsHard(s[0])) {
    t.push_back(ClosestHard(s[0], isupper(s[0])));
  } else {
    t.push_back(s[0]);
  }
  bool cross = false;
  for (int i = 1; i < s.size(); ++i) {
    if (s[i] == '-') {
      cross = true;
      continue;
    }
    if (cross) {
      if (IsHard(s[i])) t.push_back(
          isupper(s[i]) ? toupper(t[0]) : tolower(t[0]));
      else t.push_back(s[i]);
    } else {
      t.push_back(s[i]);
    }
  }
  if (IsHard(t.back())) {
    t += GetEnding(t.back());
  }

  return t;
}

int main() {
  while (std::fgets(s, kMaxN, stdin)) {
    int n = strlen(s) - 1;

    std::string w;
    for (int i = 0; i < n; ) {
      w.resize(0);
      while (i < n && s[i] != ' ') {
        w.push_back(s[i]);
        i++;
      }
      printf("%s ", Transform(w).c_str());
      if (s[i] == ' ') ++i;
    }
    printf("\n");
  }

  return 0;
}

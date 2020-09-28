#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
  int m;
  char ch;
  std::ios_base::sync_with_stdio(false);
  while (std::cin >> m) {
    std::string message;
    std::getline(std::cin, message);

    std::string word;
    std::vector<std::pair<int, std::string>> v;
    std::unordered_map<std::string, std::unordered_set<std::string>> user_messages;
    std::unordered_map<std::string, int> occ, unique_occ;

    for (int j = 0; j < m; ++j) {
      std::getline(std::cin, message);

      bool is_first = true;
      int n = message.size();
      std::unordered_set<std::string>* user_words = nullptr;
      for (int i = 0; i < n; ) {
        word.resize(0);
        while (i < n && message[i] != ' ') {
          word.push_back(message[i]);
          ++i;
        }
        ++i;
        if (is_first) {
          user_words = &user_messages[word];
          is_first = false;
          continue;
        }
        if (user_words->find(word) == user_words->end()) {
          user_words->insert(word);
          unique_occ[word]++;
        }
        occ[word]++;
      }
    }
    int k = user_messages.size();

    for (const auto& entry : unique_occ) {
      if (entry.second == k) {
        v.push_back(std::make_pair(occ[entry.first], entry.first));
      }
    }
    std::sort(v.begin(), v.end(), [](const std::pair<int, std::string>& lhs,
                                     const std::pair<int, std::string>& rhs) {
        if (lhs.first != rhs.first) return lhs.first > rhs.first;
        return lhs.second < rhs.second;
        });

    if (v.empty()) std::cout << "ALL CLEAR" << std::endl;
    for (const auto& entry : v) std::cout << entry.second << std::endl;
  }

  return 0;
}


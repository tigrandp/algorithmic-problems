#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <utility>
#include <vector>

constexpr int kMaxN = 150007;
constexpr char kPushFront[] = "pushfront";
constexpr char kPushBack[] = "pushback";
constexpr char kPopFront[] = "popfront";
constexpr char kPopBack[] = "popback";

enum class DequeOperation {
  kPushFront = 0,
  kPushBack = 1,
  kPopFront = 2,
  kPopBack = 3
};

struct Operation {
  int op1;
  int op2;
  DequeOperation op;
};

int n;
Operation operations[kMaxN];
int size[kMaxN], max_size[kMaxN];

// dequest
int arena[kMaxN * 3], tail[kMaxN], head[kMaxN];

int main() {
  freopen("deques.in", "r", stdin);
  freopen("deques.out", "w", stdout);

  while (scanf("%d", &n) == 1) {
    std::memset(arena, 0, sizeof(arena));

    int x, y;
    char buffer[20];
    for (int i = 0; i < n; ++i) {
      scanf("%s", &buffer);

      if (std::strcmp(buffer, kPushFront) == 0) {
        scanf("%d%d", &x, &y);

        size[x]++;
        max_size[x] = std::max(max_size[x], size[x]);
        operations[i] = {.op1 = x,
                         .op2 = y,
                         .op = DequeOperation::kPushFront};
      } else if (std::strcmp(buffer, kPushBack) == 0) {
        scanf("%d%d", &x, &y);

        size[x]++;
        max_size[x] = std::max(max_size[x], size[x]);
        operations[i] = {.op1 = x,
                         .op2 = y,
                         .op = DequeOperation::kPushBack};
      } else if (std::strcmp(buffer, kPopFront) == 0) {
        scanf("%d", &x);

        size[x]--;
        operations[i] = {.op1 = x,
                         .op = DequeOperation::kPopFront};
      } else if (std::strcmp(buffer, kPopBack) == 0) {
        scanf("%d", &x);

        size[x]--;
        operations[i] = {.op1 = x,
                         .op = DequeOperation::kPopBack};
      }
    }

    int cursor = 10;
    for (int i = 0; i < kMaxN; ++i) {
      if (max_size[i]) {
        head[i] = cursor + max_size[i] + 1;
        tail[i] = cursor + max_size[i];
        cursor += 2 * max_size[i] + 10;
      }
    }

    for (int i = 0; i < n; ++i) {
      if (operations[i].op == DequeOperation::kPushFront) {
        arena[--head[operations[i].op1]] = operations[i].op2;
      } else if (operations[i].op == DequeOperation::kPushBack) {
        arena[++tail[operations[i].op1]] = operations[i].op2;
      } else if (operations[i].op == DequeOperation::kPopFront) {
        printf("%d\n", arena[head[operations[i].op1]++]);
      } else if (operations[i].op == DequeOperation::kPopBack) {
        printf("%d\n", arena[tail[operations[i].op1]--]);
      }
    }
  }

  return 0;
}


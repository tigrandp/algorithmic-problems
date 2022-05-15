#include <cstdio>
#include <vector>

struct Matrix {
  Matrix(const std::vector<std::vector<int>>& mt) : n(mt.size()), m(mt) {}

  int n;
  std::vector<std::vector<int>> m;
};


void Mul(int Mod, const Matrix& a, const Matrix& b, Matrix& o) {
    Matrix c({{0, 0, 0, 0},
              {0, 0, 0, 0},
              {0, 0, 0, 0},
              {0, 0, 0, 0}});

    for (int i = 0; i < a.n; ++i) {
      for (int j = 0; j < a.n; ++j) {
        c.m[i][j] = 0;
        for (int k = 0; k < a.n; ++k) {
          c.m[i][j] += (a.m[i][k] * b.m[k][j]) % Mod;
        }
        c.m[i][j] %= Mod;
      }
    }

    for (int i = 0; i < a.n; ++i)
      for (int j = 0; j < a.n; ++j)
        o.m[i][j] = c.m[i][j];
}

Matrix BinPow(Matrix A, int n, int Mod) {
  Matrix I({{1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}});
  while (n) {
    if (n & 1)
      Mul(Mod, I, A, I);
    Mul(Mod, A, A, A);
    n >>= 1;
  }

  return I;
}

bool Ok(int P, int A, int B, int C, int Z, const Matrix& M, int V) {
  const auto& R = M.m[0];
  int T = (R[0] * A + R[1] * B + R[2] * C + R[3] * Z) % P;

  return T == V;
}

int Get(int P, int A, int B, int C, int Z, const Matrix& M) {
  const auto& R = M.m[0];
  return (R[0] * A + R[1] * B + R[2] * C + R[3] * Z) % P;
}

int main() {
  int test_case; scanf("%d", &test_case);
  while (test_case-- > 0) {
    int P; scanf("%d", &P);
    int Ax, Bx, Cx, Kx, Nx; scanf("%d%d%d%d%d", &Ax, &Bx, &Cx, &Kx, &Nx);
    int Ay, By, Cy, Ky, Ny; scanf("%d%d%d%d%d", &Ay, &By, &Cy, &Ky, &Ny);

    int X; scanf("%d", &X);

    Matrix Mx_({{0, 1, 1, 0},
                {Kx, 0, 0, 1},
                {1, Kx, 0, 0},
                {0, 0, 1, 0}});
    Matrix Mx = BinPow(Mx_, Nx, P);

    Matrix My_({{0, 1, 1, 0},
                {Ky, 0, 0, 1},
                {1, Ky, 0, 0},
                {0, 0, 1, 0}});
    Matrix My = BinPow(My_, Ny, P);

    std::vector<int> answers;
    for (int Q = 0; Q < P; ++Q)
      if (Ok(P, Ax, Bx, Cx, Q, Mx, X))
        answers.push_back(Get(P, Ay, By, Cy, Q, My));

    if (answers.size() != 1) printf("UNKNOWN\n");
    else printf("%d\n", answers[0]);
  }

  return 0;
}

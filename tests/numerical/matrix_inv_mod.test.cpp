#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
#include "../../lib/template.h"
const int mod = 998244353;
#include "../../lib/numerical/matrix_inv_mod.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin >> n;
  vec<vec<ll>> A(n, vec<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }
  int rank = matInv(A);
  if (rank == n) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cout << A[i][j] << ' ';
      }
      cout << '\n';
    }
  } else {
    cout << -1 << '\n';
  }
}


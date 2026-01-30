#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "../../lib/template.h"
const int mod = 998244353;
#include "../../lib/numerical/int_determinant.h"

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
  ll res = det(A);
  cout << res << '\n';
}


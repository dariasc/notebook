#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include "../../lib/template.h"
#include "../../lib/flow/weighted_matching.h"

signed main() {
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
  auto [X, p] = hungarian(A);
  cout << X << '\n';
  for (int i = 0; i < n; i++) {
    cout << p[i] << ' ';
  }
  cout << '\n';
}


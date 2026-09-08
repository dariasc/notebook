#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"
#include "../../lib/template.h"
const ll mod = 998244353;
#include "../../lib/numerical/berlekamp_massey.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin >> n;
  vec<ll> a(n);
  for (auto &x : a) {
    cin >> x;
  }
  if (n == 0) {
    cout << 0 << "\n\n";
    return 0;
  }
  vec<ll> c = berlekampMassey(a);
  cout << sz(c) << '\n';
  for (int i = 0; i < sz(c); i++) {
    cout << c[i] << (i + 1 == sz(c) ? "" : " ");
  }
  cout << '\n';
}

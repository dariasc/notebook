#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"
#include "../../lib/template.h"
#include "../../lib/numerical/fst.h"
#include "../../lib/nt/mod_arithmetic.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin >> n;
  vec<Mod> a, b;
  for (int i = 0; i < (1 << n); i++) {
    int x;
    cin >> x;
    a.pb(x);
  }
  for (int i = 0; i < (1 << n); i++) {
    int x;
    cin >> x;
    b.pb(x);
  }
  vec<Mod> r = conv(a, b);
  for (auto x : r) {
    cout << x << ' ';
  }
  cout << '\n';
}


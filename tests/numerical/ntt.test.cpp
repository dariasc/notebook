#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod" 
#include "../../lib/template.h"
#include "../../lib/numerical/ntt.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  vec<ll> a(n), b(m);
  for (auto &x : a) {
    cin >> x;
  }
  for (auto &x : b) {
    cin >> x;
  }
  vec<ll> r = convSmall(a, b);
  for (auto x : r) {
    cout << x << ' ';
  }
  cout << '\n';
}


#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency" 
#include "../../lib/template.h"
#include "../../lib/ds/wavelet_matrix.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<ull> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  Wavelet w(a, 1e9+1);
  while (q--) {
    int l, r, x;
    cin >> l >> r >> x;
    cout << w.count(l, r, x+1) - w.count(l, r, x) << '\n';
  }
}


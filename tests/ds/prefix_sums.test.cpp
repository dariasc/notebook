#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum" 
#include "../../lib/template.h"
#include "../../lib/ds/prefix_sums.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<ll> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  PrefixSum<ll> P(a);
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << P.sum(a, b) << '\n';
  }
}


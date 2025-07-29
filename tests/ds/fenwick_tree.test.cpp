#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum" 
#include "../../lib/template.h"
#include "../../lib/ds/fenwick_tree.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vi a(n);
  FT tree(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    tree.update(i, a[i]);
  }
  while (q--) {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 0) {
      tree.update(a, b);
    } else if (t == 1) {
      cout << tree.query(b) - tree.query(a)  << "\n";
    }
  }
}


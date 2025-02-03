#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../../lib/template.h"
#include "../../lib/ds/value.h"
#include "../../lib/ds/persistent_segment_tree.h"

void make_unique(vec<int> &a) {
  sort(all(a));
  auto last = unique(all(a));
  a.erase(last, a.end());
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<int> X(n), Y(n);
  vec<array<int, 3>> P(n);
  for (int i = 0; i < n; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    X[i] = x;
    Y[i] = y;
    P[i] = {y,x,w};
  }
  make_unique(X);
  make_unique(Y);
  sort(all(P));
  vec<int> last(sz(Y));
  SegmentTree<Value> tree(sz(X));
  int ver = 0;
  for (auto [y, x, w] : P) {
    int xi = lower_bound(all(X), x) - X.begin();
    int yi = lower_bound(all(Y), y) - Y.begin();
    ver = tree.update(ver, xi, w);
    last[yi] = ver;
  }
  while (q--) {
    int l, d, r, u;
    cin >> l >> d >> r >> u;
    int li = lower_bound(all(X), l) - X.begin();
    int ri = upper_bound(all(X), r-1) - X.begin();
    int di = lower_bound(all(Y), d) - Y.begin() - 1;
    int ui = upper_bound(all(Y), u-1) - Y.begin() - 1;
    cout << tree.query(last[ui], li, ri) - tree.query(last[di], li, ri) << "\n"; 
  }
}


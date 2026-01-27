#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"
#include "../../lib/template.h"
#include "../../lib/ds/st/persistent_lazy_segment_tree.h"
#include "range_affine_op.h"

int path_copy(auto &t, int l, int r, int k, int v) {
  return path_copy(t, l, r, k, v, 0, t.n); 
}
int path_copy(auto &t, int l, int r, int k, int v, int tl, int tr) {
  if (r <= tl || tr <= l) 
    return v;
  if (l <= tl && tr <= r) {
    return k;
  } else {
    int tm = (tl+tr)/2;
    v = t.push(v, tl, tr);
    k = t.push(k, tl, tr);
    t.s[v].l = path_copy(t, l, r, t.s[k].l, t.s[v].l, tl, tm);
    t.s[v].r = path_copy(t, l, r, t.s[k].r, t.s[v].r, tm, tr);
    t.s[v].x = mod_plus(t.s[t.s[v].l].x, t.s[t.s[v].r].x);
  }
  return v;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vi a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  SegmentTree<ll, mod_plus, 0, Tag, Tag{}> tree(n);
  vi ver(q+1);
  for (int i = 0; i < n; i++) {
    ver[0] = tree.upd(i, i+1, {0, a[i]}, ver[0]);
  }
  int i = 1;
  while (q--) {
    int t, k;
    cin >> t >> k;
    k++;
    if (t == 0) {
      int l, r;
      cin >> l >> r;
      int b, c;
      cin >> b >> c;
      ver[i] = tree.upd(l, r, {b, c}, ver[k]);
    } else if (t == 1) {
      int s;
      cin >> s;
      s++;
      int l, r;
      cin >> l >> r;
      ver[i] = path_copy(tree, l, r, ver[s], ver[k]);
    } else if (t == 2) {
      int l, r;
      cin >> l >> r;
      cout << tree.query(l, r, ver[k]) << "\n";
    }
    i++;
  }
}

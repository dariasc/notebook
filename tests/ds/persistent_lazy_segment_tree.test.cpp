#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"
#include "../../lib/template.h"
#include "../../lib/ds/persistent_lazy_segment_tree.h"
#include "range_affine_op.h"

#define L s[v].l
#define R s[v].r
#define tm (tl+tr)/2
int path_copy(auto &t, int l, int r, int k, int v, int tl=0, int tr=0) {
  if (tr == 0) tr = t.n;
  if (r <= tl || tr <= l) 
    return v;
  t.s.push_back(t.s[v]);
  v = sz(t.s) - 1;
  if (l <= tl && tr <= r) {
    return k;
  } else {
    t.push(v, tl, tr);
    t.push(k, tl, tr);
    t.L = path_copy(t, l, r, t.s[k].l, t.L, tl, tm);
    t.R = path_copy(t, l, r, t.s[k].r, t.R, tm, tr);
    t.s[v].x = Op{}(t.s[t.L].x, t.s[t.R].x);
  }
  return v;
}
#undef L
#undef R
#undef tm

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vi a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  SegmentTree<Op{}, Tag{}> tree(n);
  vi ver(q+1);
  for (int i = 0; i < n; i++) {
    ver[0] = tree.update(i, i+1, {0, a[i]}, ver[0]);
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
      ver[i] = tree.update(l, r, {b, c}, ver[k]);
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

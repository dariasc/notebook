#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"
#include "../../lib/template.h"
#include "../../lib/ds/persistent_lazy_segment_tree.h"

const ll mod = 998244353;

struct Val {
  ll x;
  operator ll() const { return x; }
  Val() : x(0) {} // identity
  Val(ll x) : x(x % mod) {} // constructor
  Val(Val a, Val b) { // merge
    x = (a.x + b.x) % mod;
  }
};

struct Tag {
  ll b = 1, c = 0; // empty update
  bool operator==(const Tag &op) const = default;
  void update(Tag op) {
    b = (b * op.b) % mod;
    c = ((c * op.b) + op.c) % mod;
  }
  template <class T>
  T apply(T val, int l, int r) {
    return {val.x * b % mod + c * (r - l) % mod};
  }
};

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
    t.s[v].x = Val(t.s[t.L].x, t.s[t.R].x);
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
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  SegmentTree<Val, Tag> tree(n);
  vec<int> ver(q+1);
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


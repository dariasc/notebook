#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"
#include "../lib/template.h"
#include "../lib/ds/persistent_lazy_segment_tree.h"

const ll mod = 998244353;

struct Value {
  ll x;
  operator ll() const { return x; }
  Value() : x(0) {} // identity
  Value(ll x) : x(x % mod) {} // constructor
  Value(Value a, Value b) { // merge
    x = (a.x + b.x) % mod;
  }
};

struct Tag {
  ll b, c;
  Tag() : b(1), c(0) {} // empty update
  Tag(ll b, ll c) : b(b), c(c) {}
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

int path_copy(auto &t, int i, int k, int l, int r, int tl, int tr) {
  if (r <= tl || tr <= l) 
    return i;
  t.s.push_back(t.s[i]);
  int j = sz(t.s) - 1;
  if (l <= tl && tr <= r) {
    return k;
  } else {
    int tm = (tl+tr)/2;
    t.push(j, tl, tr);
    t.push(k, tl, tr);
    t.s[j].l = path_copy(t, t.s[j].l, t.s[k].l, l, r, tl, tm);
    t.s[j].r = path_copy(t, t.s[j].r, t.s[k].r, l, r, tm, tr);
    t.s[j].x = Value(t.s[t.s[j].l].x, t.s[t.s[j].r].x);
  }
  return j;
}

int path_copy(auto &t, int ver, int src, int l, int r) {
  t.roots.push_back(path_copy(t, t.roots[ver], t.roots[src], l, r, 0, t.n));
  return sz(t.roots) - 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  SegmentTree<Value, Tag> tree(n);
  for (int i = 0; i < n; i++) {
    tree.update(i, i, i+1, {0, a[i]});
  }
  vec<int> ver(q+1);
  ver[0] = n;
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
      ver[i] = tree.update(ver[k], l, r, {b, c});
    } else if (t == 1) {
      int s;
      cin >> s;
      s++;
      int l, r;
      cin >> l >> r;
      ver[i] = path_copy(tree, ver[k], ver[s], l, r);
    } else if (t == 2) {
      int l, r;
      cin >> l >> r;
      cout << tree.query(ver[k], l, r) << "\n";
    }
    i++;
  }
}


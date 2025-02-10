#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum" 
#include "../../lib/template.h"
#include "../../lib/ds/lazy_segment_tree.h"

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
  void update(Tag op) {
    b = (b * op.b) % mod;
    c = ((c * op.b) + op.c) % mod;
  }
  template <class T>
  T apply(T val, int l, int r) {
    return {val.x * b % mod + c * (r - l) % mod};
  }
};

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
  tree.build(a);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) {
      int b, c;
      cin >> b >> c;
      tree.update(l, r, {b, c});
    } else if (t == 1) {
      cout << tree.query(l, r) << "\n";
    }
  }
}


#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum_large_array" 
#include "../../lib/template.h"
#include "../../lib/ds/dynamic_lazy_segment_tree.h"

const ll mod = 998244353;

struct Val {
  ll x;
  operator ll() const { return x; }
  Val(ll x = 0) : x(x % mod) {} // constructor
  Val(Val a, Val b) { // merge
    x = (a.x + b.x) % mod;
  }
};

struct Tag {
  ll b = 1, c = 0;
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
  SegmentTree<Val, Tag> tree(n);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) {
      int b, c;
      cin >> b >> c;
      tree.update(l, r, Tag{b, c});
    } else if (t == 1) {
      cout << tree.query(l, r) << "\n";
    }
  }
}


#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"
#include "../../lib/template.h"
#include "../../lib/ds/treap.h"
struct FlipNode {
  FlipNode *l = 0, *r = 0;
  int y, c = 1;
  ll x;
  ll sum;
  int flip = 0;
  FlipNode(ll x) : y(int(rng())), x(x), sum(x) {}
  FlipNode* pull() {
    c = 1;
    sum = x;
    if (l) c += l->c, sum += l->sum;
    if (r) c += r->c, sum += r->sum;
    return this;
  }
  void push() {
    if (flip) {
      swap(l, r);
      if (l) l->flip ^= 1;
      if (r) r->flip ^= 1;
    }
    flip = 0;
  }
};
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  Treap<FlipNode> tree;
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    tree.insert(tree.make_node(x), i);
  }
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) {
      if (l == r) {
        continue;
      }
      auto [b, c] = tree.split(tree.root, r);
      auto [a, m] = tree.split(b, l);
      m->flip ^= 1;
      tree.root = tree.merge(tree.merge(a, m), c);
    } else if (t == 1) {
      if (l == r) {
        cout << 0 << '\n';
        continue;
      }
      auto [b, c] = tree.split(tree.root, r);
      auto [a, m] = tree.split(b, l);
      cout << m->sum << endl;
      tree.root = tree.merge(tree.merge(a, m), c);
    }
  }
}


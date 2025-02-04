#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"
#include "../../lib/template.h"
#include "../../lib/ds/treap.h"

int smallest(auto &t, int &v) {
  if (t.s[v].l == -1) {
    int x = t.s[v].x;
    v = t.s[v].r;
    return x;
  }
  return smallest(t, t.s[v].l);
}

int biggest(auto &t, int &v) {
  if (t.s[v].r == -1) {
    int x = t.s[v].x;
    v = t.s[v].l;
    return x;
  }
  return biggest(t, t.s[v].r);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  Treap<int> tree;
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    tree.insert(x);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      n++;
      int x;
      cin >> x;
      tree.insert(x);
    } else if (t == 1) {
      n--;
      cout << smallest(tree, tree.root) << "\n";
    } else if (t == 2) {
      n--;
      cout << biggest(tree, tree.root) << "\n";
    }
  }
}


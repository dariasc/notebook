#include "splay_tree.h"
/* -
name = "Sequence Tree"
[info]
description = "Implicit splay tree for range queries/reversals."
time = "Amortized $O(log N)$"
- */
struct SeqTree : SplayTree {
  int root = 0;
  SeqTree(int n, const vec<ll>& a = {}) : SplayTree(n + 2) { // 1, n+2 sentinels
    rep(i, 0, sz(a)) T[i + 2].self = a[i];
    rep(i, 1, n + 2) set(i + 1, 0, i);
    splay(root = n + 2);
  }
  SeqTree(const vec<ll>& a) : SeqTree(sz(a), a) {}
  int kth(int k, int x = 0) { // 0-indexed within subtree
    for (x = x ?: root; ; ) {
      push(x);
      int l = T[x].ch[0], s = T[l].sz;
      if (k < s) x = l;
      else if (k == s) return splay(x), root = x;
      else k -= s + 1, x = T[x].ch[1];
    }
  }
  int node(int l, int r) { // [l, r)
    int L = kth(l), R = kth(r + 1);
    splay(root = L); splay(R, L);
    return T[R].ch[0];
  }
  void reverse(int l, int r) {
    if (l < r) T[node(l, r)].flip ^= 1;
  }
  ll query(int l, int r) {
    return l >= r ? 0 : T[node(l, r)].path;
  }
};

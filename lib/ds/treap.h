#include "../template.h"
/* -
name = "Treap"
[info]
description = "Can easily be extended to an implicit treap, and to support range queries and updates."
time = "$O(log n)$"
- */
mt19937 rng(chrono::high_resolution_clock::now()
            .time_since_epoch().count());
template <class T> struct Treap {
  struct Node {
    int l = -1, r = -1, c = 1;
    T x;
    int y;
    Node(T x) : x(x), y(int(rng())) {}
  };
  int root = -1;
  vec<Node> s;
  int cnt(int j) {
    return j != -1 ? s[j].c : 0;
  }
  void recalc(int j) {
    s[j].c = 1 + cnt(s[j].l) + cnt(s[j].r);
  }
  pair<int, int> split(int j, T k) {
    if (j == -1) return {-1, -1};
    auto n = &s[j];
    if (n->x >= k) { // "cnt(n->l) >= k" for implicit treap 
      auto [L,R] = split(n->l, k);
      n->l = R;
      recalc(j); 
      return {L, j};
    } else {
      auto [L,R] = split(n->r, k); // "k - cnt(n->l) - 1"
      n->r = L;
      recalc(j); 
      return {j, R};
    }
  }
  int merge(int l, int r) {
    if (l == -1) return r;
    if (r == -1) return l;
    if (s[l].y > s[r].y) {
      s[l].r = merge(s[l].r, r);
      return recalc(l), l;
    } else {
      s[r].l = merge(l, s[r].l);
      return recalc(r), r;
    }
  }
  void insert(T val) {
    s.push_back({val});
    auto [l, r] = split(root, val);
    root = merge(merge(l, sz(s)-1), r);
  }
};

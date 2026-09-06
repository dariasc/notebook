#include "../template.h"
/* -
name = "Splay Tree"
source = "https://codeforces.com/blog/entry/75885"
[info]
description = "Splay tree on 1-based indices. Base for LCT."
time = "Amortized $O(log N)$"
- */
struct SplayTree {
  struct Node {
    int ch[2] = {0, 0}, p = 0, sz = 1;
    ll self = 0, path = 0; // path aggregates
    ll sub = 0, vir = 0;   // subtree aggregates
    bool flip = 0;         // lazy tag
  };
  vec<Node> T;
  SplayTree(int n) : T(n + 1) { T[0].sz = 0; }
  void push(int x) {
    if (!x || !T[x].flip) return;
    int l = T[x].ch[0], r = T[x].ch[1];
    T[l].flip ^= 1, T[r].flip ^= 1;
    swap(T[x].ch[0], T[x].ch[1]);
    T[x].flip = 0;
  }
  void pull(int x) {
    int l = T[x].ch[0], r = T[x].ch[1]; push(l); push(r);
    T[x].sz = 1 + T[l].sz + T[r].sz;
    T[x].path = T[l].path + T[x].self + T[r].path;
    T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
  }
  void set(int x, int d, int y) {
    T[x].ch[d] = y; T[y].p = x; pull(x);
  }
  int dir(int x) {
    int p = T[x].p; if (!p) return -1;
    return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
  }
  void rotate(int x) {
    int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
    set(y, dx, T[x].ch[!dx]);
    set(x, !dx, y);
    if (~dy) set(z, dy, x);
    T[x].p = z;
  }
  void splay(int x, int goal = 0) {
    for (push(x); ~dir(x) && T[x].p != goal; ) {
      int y = T[x].p, z = T[y].p;
      push(z); push(y); push(x);
      int dx = dir(x), dy = dir(y);
      if (~dy && z != goal) rotate(dx != dy ? x : y);
      rotate(x);
    }
  }
};

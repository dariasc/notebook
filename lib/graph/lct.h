#include "../ds/splay_tree.h"
/* -
name = "Link Cut Tree"
source = "https://codeforces.com/blog/entry/75885"
[info]
time = "Amortized $O(log N)$"
- */
struct LinkCut : SplayTree {
  LinkCut(int n) : SplayTree(n) {}
  int access(int x) {
    int u = x, v = 0;
    for (; u; v = u, u = T[u].p) {
      splay(u);
      int& ov = T[u].ch[1];
      T[u].vir += T[ov].sub;
      T[u].vir -= T[v].sub;
      ov = v; pull(u);
    }
    return splay(x), v;
  }
  void reroot(int x) {
    access(x); T[x].flip ^= 1; push(x);
  }
  void link(int u, int v) {
    reroot(u); access(v);
    T[v].vir += T[u].sub;
    T[u].p = v; pull(v);
  }
  void cut(int u, int v) {
    reroot(u); access(v);
    T[v].ch[0] = T[u].p = 0; pull(v);
  }
  int lca(int u, int v) { // 0 if disconnected
    if (u == v) return u;
    access(u); int ret = access(v);
    return T[u].p ? ret : 0;
  }
  ll subtree(int u, int v) { // subtree of u, v outside
    reroot(v); access(u); return T[u].vir + T[u].self;
  }
  ll path(int u, int v) { // path [u..v]
    reroot(u); access(v); return T[v].path;
  }
  void update(int u, ll v) {
    access(u); T[u].self = v; pull(u);
  }
};

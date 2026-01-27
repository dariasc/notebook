#include "../template.h"
/* -
name = "Heavy Light Decomposition"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/HLD.h"
[info]
time = "$O(log^2 N)$"
description = "Decomposes a tree into vertex disjoint heavy paths and light edges such that the path from any leaf to the root contains at most $log n$ light edges. Root must be node $0$"
- */
template <bool VALS_EDGES, class T> struct HLD {
  int N, time = 0;
  vec<vi> adj;
  vi par, siz, rt, pos;
  T st;
  HLD(vec<vi> adj) : N(sz(adj)), adj(adj),
    par(N, -1), siz(N, 1), rt(N), pos(N), st(N) { 
        dfsSz(0); dfsHld(0); 
  }
  void dfsSz(int v) {
    for (int& u : adj[v]) {
      adj[u].erase(find(all(adj[u]), v));
      par[u] = v;
      dfsSz(u);
      siz[v] += siz[u];
      if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
    }
  }
  void dfsHld(int v) {
    pos[v] = time++;
    for (int u : adj[v]) {
      rt[u] = (u == adj[v][0] ? rt[v] : u);
      dfsHld(u);
    }
  }
  template <class B> void process(int u, int v, B op) {
    for (;; v = par[rt[v]]) {
      if (pos[u] > pos[v]) swap(u, v);
      if (rt[u] == rt[v]) break;
      op(pos[rt[v]], pos[v] + 1);
    }
    op(pos[u] + VALS_EDGES, pos[v] + 1);
  }
  void modifyPath(int u, int v, auto val) {
    process(u, v, [&](int l, int r) { st.upd(l, r, val); });
  }
  auto queryPath(int u, int v) { // modify depending on problem
    ll res = 0;
    process(u, v, [&](int l, int r) {
        res += st.query(l, r);
    });
    return res;
  }
  auto querySubtree(int v) { // modifySubtree is similar
    return st.query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
  }
};

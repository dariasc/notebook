#include "../template.h"
/* -
name = "Binary Lifting"
source = "https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/graphs/TreeLifting.h"
[info]
description = "Can be augmented to solve path queries without inverse."
time = "$O(log n)$"
memory = "$O(n)$"
- */
struct Lift {
  vi d, p, j;
  Lift(vec<vi>& C) : d(sz(C)), p(d), j(d) { dfs(C, 0); }
  void dfs(vec<vi>& C, int u) {
    int jmp = (d[u] + d[j[j[u]]] == 2 * d[j[u]]) ? j[j[u]] : u;
    for (int v : C[u]) if (v != p[u])
      d[v] = d[p[v] = u] + 1, j[v] = jmp, dfs(C, v); 
  }
  int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    while (d[u] > d[v]) u = d[j[u]] >= d[v] ? j[u] : p[u];
    if (u == v) return u;
    while (p[u] != p[v]) {
      if (j[u] != j[v]) u = j[u], v = j[v];
      else u = p[u], v = p[v];
    }
    return p[u]; 
  }
  int kth(int u, int k) {
    if (k > d[u]) return -1;
    k = d[u] - k;
    while (d[u] > k) u = d[j[u]] >= k ? j[u] : p[u];
    return u; 
  } 
};

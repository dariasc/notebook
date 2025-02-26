#include "../template.h"
#include "../ds/sparse_table.h"
/* -
name = "Lowest Common Ancestor"
[info]
description = "Finds lowest common ancestor with a sparse table."
time = "$O(1)$"
- */
struct LCA {
  int T = 0;
  vi time, path, ret;
  struct Val {
    int x;
    operator int() const { return x; }
    Val(int x = 1e9) : x(x) {} // constructor
    Val(Val a, Val b) { // merge
      x = min(a.x, b.x);
    }
  };
  SparseTable<Val> rmq;
  LCA(vec<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
  void dfs(vec<vi>& C, int v, int par) {
    time[v] = T++;
    for (int y : C[v]) if (y != par) {
      path.push_back(v), ret.push_back(time[v]);
      dfs(C, y, v);
    }
  }
  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
  // dist(a, b) { return depth[a] + depth[b] - 2*depth[lca(a,b)]; }
};

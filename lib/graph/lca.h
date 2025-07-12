#include "../template.h"
#include "../ds/sparse_table.h"
/* -
name = "Lowest Common Ancestor"
[info]
description = "Finds lowest common ancestor with a sparse table."
time = "$O(1)$"
memory = "$O(n log n)$"
- */
struct LCA {
  int T = 0;
  vi time, path, ret;
  struct Op {
    using T = int;
    int operator()(int a, int b) const {
      return min(a, b);
    }
  };
  SparseTable<Op{}> rmq;
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
};

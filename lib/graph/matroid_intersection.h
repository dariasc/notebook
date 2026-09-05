#include "../template.h"
/* -
name = "Matroid Intersection"
source = "https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/matroid.cpp"
[info]
description = "Algorithms for finding maximum independent sets in the intersection of two matroids. `oracle(i)` is independent after adding $i$, `oracle(i, j)` ... after swapping $i$, $j$."
time = "$O(r^2 n)$ where $r$ is the size of the independent set."
- */
vi matroidInter(int n, auto M1, auto M2) {
  vec<bool> b(n);
  vi I[2];
  bool converged = false;
  while (!converged) {
    I[0].clear(), I[1].clear();
    rep(u,0,n) I[b[u]].pb(u);
    M1.build(I[1]), M2.build(I[1]);
    vec<bool> target(n), pushed(n);
    queue<int> q;
    for (int u : I[0]) {
      target[u] = M2.oracle(u);
      if (M1.oracle(u)) pushed[u] = true, q.push(u);
    }
    vi p(n, -1); converged = true;
    while (sz(q)) {
      int u = q.front(); q.pop();
      if (target[u]) {
        converged = false;
        for (int v = u; v != -1; v = p[v]) b[v] = !b[v];
        break;
      }
      for (int v : I[!b[u]]) if (!pushed[v]) {
        if ((b[u] && M1.oracle(u, v)) ||
            (b[v] && M2.oracle(v, u)))
          p[v] = u, pushed[v] = true, q.push(v);
      }
    }
  }
  return I[1];
}

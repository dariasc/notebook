#include "../template.h"
/* -
name = "Mo Queries"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/MoQueries.h"
[info]
description = "Answer interval or tree path queries by finding an approximate TSP through the queries, and moving from one query to the next by adding/removing points at the ends. If values are on tree edges, change `step` to add/remove the edge $(a, c)$ and remove the initial `add` call (but keep `in`)."
time = "$O(n sqrt(q))$"
- */
void add(int ind, int end); // add a[ind] (end = 0 or 1)
void del(int ind, int end); // remove a[ind]
int calc(); // compute current answer
vi mo(vec<array<int, 2>>& Q) {
  int L = 0, R = 0, blk = 350; // ~N/sqrt(Q)
  vi s(sz(Q)), res = s;
#define K(x) pii(x[0]/blk, x[1] ^ -(x[0]/blk & 1))
  iota(all(s), 0);
  sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
  for (int qi : s) {
    auto q = Q[qi];
    while (L > q[0]) add(--L, 0);
    while (R < q[1]) add(R++, 1);
    while (L < q[0]) del(L++, 0);
    while (R > q[1]) del(--R, 1);
    res[qi] = calc();
  }
#undef K
  return res;
}
vi moTree(vec<array<int, 2>>& Q, vec<vi>& ed, int root=0){
  int N = sz(ed), pos[2] = {}, blk = 350; // ~N/sqrt(Q)
  vi s(sz(Q)), res = s, I(N), L(N), R(N), in(N), par(N);
  add(0, 0), in[0] = 1;
  auto dfs = [&](int x, int p, int dep, auto& f) -> void {
    par[x] = p;
    L[x] = N;
    if (dep) I[x] = N++;
    for (int y : ed[x]) if (y != p) f(y, x, !dep, f);
    if (!dep) I[x] = N++;
    R[x] = N;
  };
  dfs(root, -1, 0, dfs);
#define K(x) pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]] / blk & 1))
  iota(all(s), 0);
  sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
  for (int qi : s) rep(end,0,2) {
    int &a = pos[end], b = Q[qi][end], i = 0;
#define step(c) { if (in[c]) { del(a, end); in[a] = 0; } \
                  else { add(c, end); in[c] = 1; } a = c; }
    while (!(L[b] <= L[a] && R[a] <= R[b]))
      I[i++] = b, b = par[b];
    while (a != b) step(par[a]);
    while (i--) step(I[i]);
    if (end) res[qi] = calc();
  }
#undef K
#undef step
  return res;
}

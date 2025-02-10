#include "../template.h"
/* -
name = "Compressed Fenwick Tree 2D"
[info]
description = "2D fenwick tree with compressed $y$ axis, with point addition and sum range queries. Call `fakeUpdate` on the positions that will receive updates before `init`."
time = "$O(log^2 n)$"
- */
#include "fenwick_tree.h"
struct FT2 {
  vec<vi> ys; vec<FT> ft;
  FT2(int lim_x) : ys(lim_x) {}
  void fakeUpdate(int x, int y) {
    for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
  }
  void init() {
    for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
  }
  int ind(int x, int y) {
    return int(lower_bound(all(ys[x]), y) - ys[x].begin()); 
  }
  void update(int x, int y, ll dif) {
    for (; x < sz(ys); x |= x + 1)
      ft[x].update(ind(x, y), dif);
  }
  ll query(int x, int y) {
    ll sum = 0;
    for (; x; x &= x - 1)
      sum += ft[x-1].query(ind(x-1, y));
    return sum;
  }
};

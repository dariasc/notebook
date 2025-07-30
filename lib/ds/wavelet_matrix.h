#include "../template.h"
#include "bit_vector.h"
/* -
name = "Wavelet Matrix"
source = "https://github.com/programming-team-code/programming_team_code/blob/dev/library/data_structures/seg_tree_uncommon/wavelet_matrix.hpp"
[info]
description = "Supports quantile and rank queries in some range $[l, r)$."
time = "$O(log sigma)$"
space = "$O((n log sigma) / 64$)"
- */
struct Wavelet {
  int n;
  vec<BitVec> bv;
  Wavelet(vec<ull> a, ull sigma) :
    n(sz(a)), bv(bit_width(sigma), {{}}) {
    for (int h = sz(bv); h--;) {
      int i = 0;
      vec<bool> b(n);
      ranges::stable_partition(a,
        [&](ull x) { return b[i++] = (~x >> h) & 1; });
      bv[h] = b;
    }
  }
  ull kth(int l, int r, int k) {
    ll res = 0;
    for (int h = sz(bv); h--;) {
      int l0 = bv[h].rank(l), r0 = bv[h].rank(r);
      if (k < r0 - l0) l = l0, r = r0;
      else
        k -= r0 - l0, res |= 1ULL << h,
          l += bv[h].rank(n) - l0, r += bv[h].rank(n) - r0;
    }
    return res;
  }
  int count(int l, int r, ull ub) {
    int res = 0;
    for (int h = sz(bv); h--;) {
      int l0 = bv[h].rank(l), r0 = bv[h].rank(r);
      if ((~ub >> h) & 1) l = l0, r = r0;
      else
        res += r0 - l0, l += bv[h].rank(n) - l0,
          r += bv[h].rank(n) - r0;
    }
    return res;
  }
};

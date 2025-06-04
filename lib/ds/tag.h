#include "../template.h"
/* -
name = "Tag Type"
[info]
description = "Tag operator type used for lazy propagation in lazy structures."
- */
struct Tag {
  ll e = 0;
  ll apply(ll x, ll u, int l, int r) const {
    return x + u * (r - l);
  }
  ll operator()(ll lz, ll u) const {
    return lz + u;
  }
};

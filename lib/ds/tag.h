#include "../template.h"
/* -
name = "Tag Type"
[info]
description = "Tag operator type used for lazy propagation in lazy structures."
- */
struct Tag {
  using U = ll;
  U e = 0;
  ll apply(ll x, U u, int l, int r) const {
    return x + u * (r - l);
  }
  U operator()(U lz, U u) const {
    return lz + u;
  }
};

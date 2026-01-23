#include "../template.h"
/* -
name = "Tag Type"
[info]
description = "Tag operator type used for lazy propagation in lazy structures."
- */
struct Tag {
  ll u;
  ll map(ll x, int l, int r) const {
    return x + u * (r - l);
  }
  Tag operator()(U u) const {
    return lz + u;
  }
};

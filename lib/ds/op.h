#include "../template.h"
/* -
name = "Operator Type"
[info]
description = "Operator type for structures that need some merge function."
- */
struct Op {
  ll e = 0;
  ll operator()(ll a, ll b) const {
    return a + b;
  }
  ll update(ll x, ll u) const {
    return x + u;
  }
};

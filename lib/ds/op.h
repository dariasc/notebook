#include "../template.h"
/* -
name = "Operator Type"
[info]
description = "Operator type for structures that need some merge function."
- */
struct Op {
  using T = ll;
  using U = ll;
  T e = 0;
  T operator()(T a, T b) const {
    return a + b;
  }
  T update(T x, U u) const {
    return x + u;
  }
};

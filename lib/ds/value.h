#include "../template.h"
/* -
name = "Value Type"
[info]
description = "Value type for structures that need some merge function."
- */
struct Val {
  ll x;
  operator ll() const { return x; }
  Val() : x(0) {} // identity
  Val(ll x) : x(x) {} // constructor
  Val(Val a, Val b) { // merge
    x = a.x + b.x;
  }
  void update(Val b) { // point update
    x += b.x; 
  }
};

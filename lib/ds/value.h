#include "../template.h"
/* -
name = "Value Type"
[info]
description = "Value type for structures that need some merge function."
- */
struct Value {
  ll x;
  operator ll() const { return x; }
  Value() : x(0) {} // identity
  Value(ll x) : x(x) {} // constructor
  Value(Value a, Value b) { // merge
    x = a.x + b.x;
  }
  void update(Value b) { 
    x += b.x; 
  }
};

#include "../template.h"
/* -
name = "Tag Type"
[info]
description = "Tag type used for lazy propagation in lazy structures."
- */
struct Tag {
  ll set = -1, add = 0; // empty update
  void update(Tag op) {
    if (op.set != -1)
      set = op.set, add = 0;
    add += op.add;
  }
  template <class T>
  T apply(T val, int l, int r) {
    if (set != -1)
      return {(set + add) * (r - l)};
    return {val.x + add * (r - l)};
  }
};

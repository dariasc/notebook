#include "../template.h"
/* -
name = "Tag Type"
[info]
description = "Tag type used for lazy propagation in lazy structures. Example has range `add` and `set`."
- */
struct Tag {
  ll set, add;
  Tag() : set(-1), add(0) {} // empty update
  Tag(ll set, ll add) : set(set), add(add) {}
  void update(Tag op) {
    if (op.set != -1) {
      set = op.set;
      add = 0;
    }
    add += op.add;
  }
  template <class T>
  T apply(T val, int l, int r) {
    if (set != -1) {
      return {(set + add) * (r - l)};
    }
    return {val.x + add * (r - l)};
  }
};

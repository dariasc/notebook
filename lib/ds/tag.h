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
  auto operator<=>(const Tag&) const = default;
  void update(Tag op) {
    if (op.set != -1) {
      set = op.set;
      add = 0;
    }
    add += op.add;
  }
  Value eval(int lo, int hi, Value val) {
    if (set != -1) {
      return {(set + add) * (hi - lo)};
    }
    return {val.x + add * (hi - lo)};
  }
};

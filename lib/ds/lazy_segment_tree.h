#include "../template.h"
#include "value.h"
#include "tag.h"
/* -
name = "Lazy Segment Tree"
[info]
description = "Lazy segment tree, implemented with pointers, supports range queries and updates."
time = "$O(log n)$"
- */
template <class T, class U> struct Node {
  Node *l = 0, *r = 0;
  int lo, hi;
  T val;
  U tag = U();
  Node(vec<T> &v, int lo, int hi) : lo(lo), hi(hi) {
    if (lo + 1 < hi) {
      int mid = lo + (hi - lo) / 2;
      l = new Node(v, lo, mid);
      r = new Node(v, mid, hi);
      val = T(l->eval(), r->eval());
      return;
    }
    val = v[lo];
  }
  T eval() { return tag.eval(lo, hi, val); }
  T query(int L, int R) {
    if (R <= lo || hi <= L)
      return T();
    if (L <= lo && hi <= R)
      return eval();
    push();
    return T(l->query(L, R), r->query(L, R));
  }
  void update(int L, int R, U x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R) {
      tag.update(x);
    } else {
      push();
      l->update(L, R, x), r->update(L, R, x);
      val = T(l->eval(), r->eval());
    }
  }
  void push() {
    if (tag != U()) {
      val = eval();
      l->update(lo, hi, tag), r->update(lo, hi, tag);
      tag = U();
    }
  }
  // search for first prefix in [L, R) satisfying T.pred()
  int search(int L, int R, T target) {
    T left;
    return search(L, R, target, left);
  }
  int search(int L, int R, T target, T &left) {
    if (R <= lo || hi <= L)
      return -1;
    if (L <= lo && hi <= R) {
      if (not T(left, eval()).pred(target)) {
        left = T(left, eval());
        return -1;
      }
      if (lo + 1 == hi) {
        return lo;
      }
    }
    push();
    int i = l->search(L, R, target, left);
    if (i != -1)
      return i;
    return r->search(L, R, target, left);
  }
};

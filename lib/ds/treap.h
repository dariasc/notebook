#include "../template.h"
/* -
name = "Implicit Treap"
[info]
description = "Can easily be changed to a normal treap by changing split condition."
time = "$O(log n)$"
- */
template <class T> struct Treap {
  T* root = 0;
  deque<T> s;
  template <class V>
  T* make_node(V x) {
    s.emplace_back(x);
    return &s.back();
  }
  int cnt(T* v) {
    return v ? v->c : 0;
  }
  pair<T*, T*> split(T* v, int k) { // [0, k), [k, n)
    if (!v) return {};
    v->push();
    if (cnt(v->l) >= k) { // "n->x >= k" for set 
      auto [L, R] = split(v->l, k);
      v->l = R;
      return {L, v->pull()};
    } else {
      auto [L, R] = split(v->r, k - cnt(v->l) - 1); // "k"
      v->r = L;
      return {v->pull(), R};
    }
  }
  T* merge(T* l, T* r) {
    if (!l || !r) return l ? l : r;
    l->push(), r->push();
    if (l->y > r->y) {
      l->r = merge(l->r, r);
      return l->pull();
    } else {
      r->l = merge(l, r->l);
      return r->pull();
    }
  }
  void insert(T* v, int k) { // example
    auto [L, R] = split(root, k);
    root = merge(merge(L, v), R);
  }
};

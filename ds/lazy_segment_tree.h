/* -
name = "lazy_segment_tree"
[info]
description = "Lazy segment tree, implemented with pointers, supports range queries and updates. Example has range `add` and `set`."
time = "$O(log n)$"
- */
struct value {
  ll x;
  value() : x(0) {}
  value(ll x) : x(x) {}
  value(value &a, value &b) {
    x = a.x + b.x;
  }
};

struct tag {
  ll set, add;
  tag() : set(0), add(0) {}
  void update(tag &op) {
    if (op.set) {
      set = op.set;
      add = 0;
    } else {
      add += op.add;
    }
  }
  value eval(int lo, int hi, value &val) {
    if (set) {
      return {(set + add)*(hi - lo)};
    }
    return {val.x + add*(hi - lo)};
  }
};

template <class T, class U>
struct node {
    node *l = 0, *r = 0;
    int lo, hi;
  T val;
  U tag = tag();
    node(vec<T>& v, int lo, int hi) : lo(lo), hi(hi) {
        if (lo + 1 < hi) {
            int mid = lo + (hi - lo)/2;
            l = new node(v, lo, mid); r = new node(v, mid, hi);
            val = T(l->eval(), r->eval());
      return;
        }
        val = v[lo];
    }
  T eval() {
    return tag.eval(lo, hi, val);
  }
    T query(int L, int R) {
        if (R <= lo || hi <= L) return T();
        if (L <= lo && hi <= R) return eval();
        push();
        return T(l->query(L, R), r->query(L, R));
    }
    void update(int L, int R, U x) {
        if (R <= lo || hi <= L) return;
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
      val = val();
            l->update(lo, hi, tag), r->update(lo, hi, tag);
      tag = U();
    }
    }
};

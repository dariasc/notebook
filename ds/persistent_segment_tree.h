/* -
name = "persistent_segment_tree"
[info]
description = "Persistent segment tree, same as `lazy_segment_tree` but with history."
time = "$O(log n)$"
- */
template <class T, class U>
struct node {
	node *l = 0, *r = 0;
	int lo, hi;
  T val;
  U tag = tag();
  node(node &o) {
    l = o.l, r = o.r;
    lo = o.lo, r = o.hi;
    val = o.val, tag = o.tag;
  }
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
    auto N = push();
		return T(N->l->query(L, R), N->r->query(L, R));
	}
	node* update(int L, int R, U x) {
		if (R <= lo || hi <= L) return this;
    node *N;
		if (L <= lo && hi <= R) {
      N = new node(this);
      N->tag.update(x);
		} else {
			N = push();
      N->l = l->update(L, R, x);
      N->r = r->update(L, R, x);
			N->val = T(l->eval(), r->eval());
		}
    return N;
	}
	node* push() {
		if (tag != U()) {
      auto N = new node(this);
      N->val = val();
			N->l = l->update(lo, hi, tag);
      N->r = r->update(lo, hi, tag);
      N->tag = U();
      return N;
    }
    return this;
	}
};

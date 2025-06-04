#include "../template.h"
/* -
name = "Fenwick Tree"
[info]
description = "Fenwick tree, with point addition and sum range queries."
time = "$O(log n)$"
- */
struct FT {
  vec<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) { // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) { // [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
  int lower_bound(ll sum) { // s[0, pos] >= sum
    // returns n if no pos satisfies >= sum.
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    }
    return pos;
  }
};

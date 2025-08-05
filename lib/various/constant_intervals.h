#include "../template.h"
/* -
name = "Constant Intervals"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/various/ConstantIntervals.h"
[info]
description = "Split a monotone function on $[\"from\", \"to\")$ into a minimal set of half-open intervals on which it has the same value. Runs a callback `g` for each such interval."
usage = "`constantIntervals(0, sz(v), [&](int x) {return v[x];}, [&](int lo, int hi, T val) {...});`"
time = "$O(k log n/k)$"
- */
template<class F, class G, class T>
void rec(int from, int to, F& f, G& g, int& i, T& p, T q) {
  if (p == q) return;
  if (from == to) {
    g(i, to, p);
    i = to; p = q;
  } else {
    int mid = (from + to) >> 1;
    rec(from, mid, f, g, i, p, f(mid));
    rec(mid+1, to, f, g, i, p, q);
  }
}
template<class F, class G>
void constantIntervals(int from, int to, F f, G g) {
  if (to <= from) return;
  int i = from; auto p = f(i), q = f(to-1);
  rec(from, to-1, f, g, i, p, q);
  g(i, to, q);
}

#include "../template.h"
/* -
name = "Interval Cover"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/various/IntervalCover.h"
[info]
description = "Compute indices of smallest set of intervals covering another interval. Intervals should be $[\"inclusive\", \"exclusive\")$. To support $[\"inclusive\", \"inclusive\"]$, change while to add `|| R.empty()`. Returns empty set on failure (or if G is empty)."
time = "$O(n log n)$"
- */
template<class T>
vi cover(pair<T, T> G, vec<pair<T, T>> I) {
  vi S(sz(I)), R;
  iota(all(S), 0);
  sort(all(S), [&](int a, int b) { return I[a] < I[b]; });
  T cur = G.first;
  int at = 0;
  while (cur < G.second) {
    pair<T, int> mx = make_pair(cur, -1);
    while (at < sz(I) && I[S[at]].first <= cur) {
      mx = max(mx, make_pair(I[S[at]].second, S[at]));
      at++;
    }
    if (mx.second == -1) return {};
    cur = mx.first;
    R.push_back(mx.second);
  }
  return R;
}

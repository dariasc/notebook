#include "../template.h"
/* -
name = "Interval Container"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/various/IntervalContainer.h"
[info]
description = "Add and remove intervals from a set of disjoint intervals. Will merge the added interval with any overlapping intervals in the set when adding.  Intervals are $[\"inclusive\", \"exclusive\")$"
time = "$O(log n)$"
- */
set<pii>::iterator addInterval(set<pii>& is, int L, int R) {
  if (L == R) return is.end();
  auto it = is.lower_bound({L, R}), before = it;
  while (it != is.end() && (*it)[0] <= R) {
    R = max(R, (*it)[1]);
    before = it = is.erase(it);
  }
  if (it != is.begin() && (*--it)[1] >= L) {
    L = min(L, (*it)[0]);
    R = max(R, (*it)[1]);
    is.erase(it);
  }
  return is.insert(before, {L,R});
}
void removeInterval(set<pii>& is, int L, int R) {
  if (L == R) return;
  auto it = addInterval(is, L, R);
  auto r2 = (*it)[1];
  if ((*it)[0] == L) is.erase(it);
  else (int&)(*it)[1] = L;
  if (R != r2) is.insert({R, r2});
}

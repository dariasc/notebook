#include "../template.h"
/* -
name = "Hill Climbing"
[info]
description = "Poor man's optimization for unimodal functions. Finds local minimum by exploring neighboring points."
time = "$O(\"iterations\")$"
- */
using P = array<double, 2>;
template<class F> pair<double, P> hillClimb(P start, F f) {
  pair<double, P> cur(f(start), start);
  for (double jmp = 1e9; jmp > 1e-20; jmp /= 2) {
    rep(j,0,100) rep(dx,-1,2) rep(dy,-1,2) {
      P p = cur.second;
      p[0] += dx*jmp;
      p[1] += dy*jmp;
      cur = min(cur, make_pair(f(p), p));
    }
  }
  return cur;
}

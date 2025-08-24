#include "../template.h"
/* -
name = "Knuth DP Optimization"
[info]
description = "When doing DP on intervals: $a_(i,j) = min_(i < k < j) a_(i,k) + a_(k,j) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$, one can solve intervals in increasing order of length, and search $k = p_(i,j)$ for $a_(i,j)$ only between $p_(i,j-1)$ and $p_(i+1,j)$. This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) <= f(a,d)$ and $f(a,c) + f(b,d) <= f(a,d) + f(b,c)$ for all $a <= b <= c <= d$."
time = "$O(N^2)$"
- */


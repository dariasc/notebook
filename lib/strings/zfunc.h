#include "../template.h"
/* -
name = "Z-function"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Zfunc.h"
[info]
description = "`z[i]` computes the length of the longest common prefix of `s[i:]` and s, except `z[0] = 0`. (`abacaba` $->$ `0010301`)"
time = "$O(n)$"
- */
vi Z(const string& S) {
  vi z(sz(S));
  int l = -1, r = -1;
  rep(i,1,sz(S)) {
    z[i] = i >= r ? 0 : min(r - i, z[i - l]);
    while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
      z[i]++;
    if (i + z[i] > r)
      l = i, r = i + z[i];
  }
  return z;
}

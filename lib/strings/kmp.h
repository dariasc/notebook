#include "../template.h"
/* -
name = "KMP"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/KMP.h"
[info]
description = "`pi[x]` computes the length of the longest prefix of `s` that ends at `x`, other than `s[0...x]` itself (`abacaba` $->$ `0010123`). Can be used to find all occurrences of a string."
time = "$O(n)$"
- */
vi pi(const string &s) {
  vi p(sz(s));
  for (int i = 1; i < sz(s); i++) {
    int g = p[i - 1];
    while (g && s[i] != s[g])
      g = p[g - 1];
    p[i] = g + (s[i] == s[g]);
  }
  return p;
}

vi match(const string &s, const string &pat) {
  vi p = pi(pat + '\0' + s), res;
  for (int i = sz(p) - sz(s); i < sz(p); i++) {
    if (p[i] == sz(pat))
      res.push_back(i - 2 * sz(pat));
  }
  return res;
}

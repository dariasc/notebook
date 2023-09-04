#include "../template.h"
/* -
name = "kmp"
[info]
description = "`pi[x]` computes the length of the longest prefix of `s` that ends at `x`, other than `s[0...x]` itself (`abacaba` $->$ `0010123`). Can be used to find all occurrences of a string."
time = "$O(n)$"
- */
vec<int> pi(const string &s) {
  vec<int> p(s.size());
  for (int i = 0; i < s.size(); i++) {
    int g = p[i - 1];
    while (g && s[i] != s[g])
      g = p[g - 1];
    p[i] = g + (s[i] == s[g]);
  }
  return p;
}

vec<int> match(const string &s, const string &pat) {
  vec<int> p = pi(pat + '\0' + s), res;
  for (int i = p.size() - s.size(); i < p.size(); i++) {
    if (p[i] == pat.size())
      res.push_back(i - 2 * pat.size());
  }
  return res;
}

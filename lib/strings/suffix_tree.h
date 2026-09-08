#include "../template.h"
/* -
name = "Suffix Tree"
source = "https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/SuffixTree.h"
[info]
description = "Ukkonen's algorithm for online suffix tree construction. Each node contains indices $[l, r)$ into the string, and a list of child nodes. Suffixes are given by traversals of this tree, joining $[l, r)$ substrings. The root is $0$ (has $l = -1$, $r = 0$), non-existent children are $-1$. To get a complete tree, append a dummy symbol -- otherwise it may contain an incomplete path (still useful for substring matching, though)."
time = "$O(26 N)$"
- */
template <int ALPHA = 28> struct SuffixTree {
  struct Node {
    int l = -1, r = 0, p = 0, s = 0;
    array<int, ALPHA> to;
    Node(int l = -1, int r = 0, int p = 0)
      : l(l), r(r), p(p) { to.fill(-1); }
  };
  int toi(char c) { return c - 'a'; }
  string a;
  vec<Node> t;
  int v = 0, q = 0;
  void ukkadd(int i, int c) { suff:
    if (t[v].r <= q) {
      if (t[v].to[c] == -1) {
        t[v].to[c] = sz(t);
        t.emplace_back(i, sz(a), v);
        v = t[v].s; q = t[v].r; goto suff;
      }
      v = t[v].to[c]; q = t[v].l;
    }
    if (q == -1 || c == toi(a[q])) q++; else {
      int m = sz(t);
      t.emplace_back(t[v].l, q, t[v].p);
      t.emplace_back(i, sz(a), m);
      t[m].to[c] = m + 1; t[m].to[toi(a[q])] = v;
      t[v].l = q; t[v].p = m;
      t[t[m].p].to[toi(a[t[m].l])] = m;
      v = t[t[m].p].s; q = t[m].l;
      while (q < t[m].r) {
        v = t[v].to[toi(a[q])]; q += t[v].r - t[v].l;
      }
      if (q == t[m].r) t[m].s = v; else t[m].s = m + 2;
      q = t[v].r - (q - t[m].r); goto suff;
    }
  }
  SuffixTree(string a) : a(a) {
    t.reserve(2 * sz(a) + 2);
    t.emplace_back(-1, 0, 0);
    t.emplace_back(-1, 0, 0);
    t[1].to.fill(0); t[0].s = 1;
    rep(i,0,sz(a)) ukkadd(i, toi(a[i]));
  }
  // example: find longest common substring (uses ALPHA = 28)
  pii best{};
  int lcs(int node, int i1, int i2, int olen) {
    if (t[node].l <= i1 && i1 < t[node].r) return 1;
    if (t[node].l <= i2 && i2 < t[node].r) return 2;
    int mask = 0, len = node ? olen + t[node].r - t[node].l : 0;
    rep(c,0,ALPHA) if (t[node].to[c] != -1)
      mask |= lcs(t[node].to[c], i1, i2, len);
    if (mask == 3)
      best = max(best, {len, t[node].r - len});
    return mask;
  }
  static pii LCS(string s, string t) {
    SuffixTree st(s + char('z' + 1) + t + char('z' + 2));
    st.lcs(0, sz(s), sz(s) + 1 + sz(t), 0);
    return st.best;
  }
};

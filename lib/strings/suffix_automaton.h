#include "../template.h"
/* -
name = "Suffix Automaton"
source = "https://github.com/IvanRenison/kactlpp/blob/gmat/content/strings/SuffixAutomaton.h"
[info]
description = "Exactly all substrings of $s$ appear in states (each state represents one or more substrings); if $t$ is the longest string of state $v$ then `v.len = |t|` and every string in $v$ occurs only as a suffix of $t$ (the other suffixes of $t$ are found by following `v.l`), $p$ is the state for $s$ so terminal states lie on the suffix-link path from $p$ to the root, suffix links form the suffix tree of reversed $s$; automaton size $<= 2N$ states and $<= 3N$ transitions, extend amortized (adds 1–2 states, may change many links). Use `T = ll` for large alphabets, reserve $2N$ and prefer vector/unordered_map over map for speed."
time = "$O(N log K)$"
- */
template <class T = char> struct SuffixAutomaton {
  struct State { ll len = 0, l = -1; map<T, ll> t; };
  vector<State> s{1}; ll p = 0;
  void extend(T c) {
    ll k = SZ(s), q; s.pb({s[p].len+1});
    for(;p != -1 && !s[p].t.count(c); p = s[p].l)s[p].t[c] = k;
    if (p == -1) s[k].l = 0;
    else if (s[p].len + 1 == s[q = s[p].t[c]].len) s[k].l = q;
    else {
      s.pb(s[q]), s.back().len = s[p].len + 1;
      for (; p!=-1 && s[p].t[c]==q; p=s[p].l) s[p].t[c] = k+1;
      s[q].l = s[k].l = k+1;
    }
    p = k;
  }
};

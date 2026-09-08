#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "../../lib/template.h"
#include "../../lib/strings/suffix_automaton.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  string s;
  cin >> s;
  SuffixAutomaton sa;
  sa.s.reserve(2 * sz(s));
  for (char c : s) {
    sa.extend(c);
  }
  ll ans = 0;
  for (int i = 1; i < sz(sa.s); i++) {
    ans += sa.s[i].len - sa.s[sa.s[i].l].len;
  }
  cout << ans << '\n';
}

#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "../../lib/template.h"
#include "../../lib/strings/suffix_tree.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  string s;
  if (!(cin >> s)) return 0;
  SuffixTree st(s + char('z' + 1));
  ll ans = 0;
  for (int i = 2; i < sz(st.t); i++) {
    int l = st.t[i].l, r = min(st.t[i].r, sz(s));
    if (r > l) ans += (r - l);
  }
  cout << ans << '\n';
}

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"
#include "../../lib/template.h"
#include "../../lib/strings/kmp.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  string t, p;
  if (!(cin >> t >> p)) return 0;
  vi ans = match(t, p);
  for (int idx : ans) {
    cout << idx << '\n';
  }
}

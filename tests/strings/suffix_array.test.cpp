#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray" 
#include "../../lib/template.h"
#include "../../lib/strings/suffix_array.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  string s;
  cin >> s;
  SuffixArray S(s);
  for (int i = 0; i < sz(s); i++) {
    cout << S.sa[i+1] << " ";
  }
  cout << '\n';
}


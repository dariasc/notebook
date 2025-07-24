#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes" 
#include "../../lib/template.h"
#include "../../lib/strings/manacher.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  string s;
  cin >> s;
  auto [even, odd] = manacher(s);
  for (int i = 0; i < sz(s); i++) {
    if (i != 0) {
      cout << even[i]*2 << ' ';
    }
    cout << odd[i]*2+1 << ' ';
  }
  cout << '\n';
}


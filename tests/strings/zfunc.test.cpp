#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm" 
#include "../../lib/template.h"
#include "../../lib/strings/zfunc.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  string s;
  cin >> s;
  vi z = Z(s);
  z[0] = sz(s);
  for (auto x : z) {
    cout << x << ' ';
  }
  cout << '\n';
}


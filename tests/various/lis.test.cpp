#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence" 
#include "../../lib/template.h"
#include "../../lib/various/lis.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin >> n;
  vi a(n);
  for (auto &x : a) {
    cin >> x;
  }
  vi I = lis(a);
  cout << sz(I) << '\n';
  for (int i : I) {
    cout << i << " ";
  }
  cout << '\n';
}


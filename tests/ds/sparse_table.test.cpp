#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq" 
#include "../../lib/template.h"
#include "../../lib/ds/sparse_table.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vi a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  SparseTable<int> rmq(a);
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << rmq.query(a, b) << '\n';
  }
}


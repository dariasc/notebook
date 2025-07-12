#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq" 
#include "../../lib/template.h"
#include "../../lib/ds/sparse_table.h"

struct Op {
  using T = int;
  int operator()(int a, int b) const {
    return min(a, b);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  SparseTable<Op{}> rmq(a);
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << rmq.query(a, b) << '\n';
  }
}


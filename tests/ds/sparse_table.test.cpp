#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq" 
#include "../../lib/template.h"
#include "../../lib/ds/sparse_table.h"

struct Value {
  ll x;
  operator ll() const { return x; }
  Value() : x(0) {} // identity
  Value(ll x) : x(x) {} // constructor
  Value(Value a, Value b) { // merge
    x = min(a.x, b.x);
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
  SparseTable<Value> rmq(a);
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << rmq.query(a, b) << '\n';
  }
}


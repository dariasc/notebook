#define PROBLEM "https://judge.yosupo.jp/problem/static_range_count_distinct" 
#include "../../lib/template.h"
#include "../../lib/ds/mo.h"

int cnt = 0;
vi a, F;
void add(int ind, int end) {
  if (F[a[ind]] == 0) {
    cnt++;
  }
  F[a[ind]]++;
}
void del(int ind, int end) {
  F[a[ind]]--;
  if (F[a[ind]] == 0) {
    cnt--;
  }
}
int calc() {
  return cnt;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, q;
  cin >> n >> q;
  a = vi(n);
  F = vi(n);
  for (int &x : a) {
    cin >> x;
  }
  vi b = a;
  sort(all(b));
  auto last = unique(all(b));
  b.erase(last, b.end());
  for (int i = 0; i < n; i++) {
    a[i] = lower_bound(all(b), a[i]) - b.begin();
  }
  vec<array<int, 2>> Q(q);
  for (int i = 0; i < q; i++) {
    cin >> Q[i][0] >> Q[i][1]; 
  }
  vi r = mo(Q);
  for (int x : r) {
    cout << x << '\n';
  }
}


#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "../../lib/template.h"
#include "../../lib/ds/hashmap.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int q;
  cin >> q;
  gp_hash_table<ll, ll, chash> table({}, {}, {}, {}, {1 << 16});
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      ll k, v;
      cin >> k >> v;
      table[k] = v;
    } else {
      ll k;
      cin >> k;
      cout << table[k] << '\n';
    }
  }
}

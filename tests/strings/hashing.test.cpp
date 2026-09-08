#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"
#include "../../lib/template.h"
#include "../../lib/strings/hashing.h"
#include "../../lib/ds/hashmap.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  string s, t;
  if (!(cin >> s >> t)) return 0;
  int n = sz(s), m = sz(t);
  bool swapped = false;
  if (n > m) {
    swap(s, t);
    swap(n, m);
    swapped = true;
  }

  HashInterval hs(s), ht(t);

  int low = 1, high = n;
  int sa = 0, sb = 0, tc = 0, td = 0;

  while (low <= high) {
    int mid = low + (high - low) / 2;
    gp_hash_table<ll, int, chash> hm({}, {}, {}, {}, {1 << 19});
    for (int i = 0; i + mid <= n; i++) {
      hm[hs.hashInterval(i, i + mid).get()] = i;
    }
    int found_s = -1, found_t = -1;
    for (int j = 0; j + mid <= m; j++) {
      auto it = hm.find(ht.hashInterval(j, j + mid).get());
      if (it != hm.end()) {
        found_s = it->second;
        found_t = j;
        break;
      }
    }
    if (found_s != -1) {
      sa = found_s; sb = found_s + mid;
      tc = found_t; td = found_t + mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  if (swapped) {
    swap(sa, tc);
    swap(sb, td);
  }

  cout << sa << " " << sb << " " << tc << " " << td << '\n';
}


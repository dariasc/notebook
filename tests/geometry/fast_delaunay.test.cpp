#define PROBLEM "https://judge.yosupo.jp/problem/euclidean_mst"
#include "../../lib/template.h"
#include "../../lib/geometry/fast_delaunay.h"
#include "../../lib/ds/uf.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  if (!(cin >> n)) return 0;
  if (n <= 1) return 0;

  vec<pair<P, int>> inp(n);
  for (int i = 0; i < n; i++) {
    cin >> inp[i].first.x >> inp[i].first.y;
    inp[i].second = i;
  }
  sort(all(inp));

  vec<P> pts;
  vec<int> orig_id;
  vec<pii> mst_edges;
  UnionFind dsu(n);

  for (int i = 0; i < n;) {
    int j = i + 1;
    while (j < n && inp[j].first == inp[i].first) {
      mst_edges.push_back({inp[i].second, inp[j].second});
      dsu.join(inp[i].second, inp[j].second);
      j++;
    }
    pts.push_back(inp[i].first);
    orig_id.push_back(inp[i].second);
    i = j;
  }

  int m = sz(pts);
  if (m >= 2) {
    auto tri = triangulate(pts);
    struct Edge {
      ll w;
      int u, v;
      bool operator<(const Edge& o) const { return w < o.w; }
    };
    vec<Edge> edges;
    if (tri.empty()) {
      for (int i = 0; i + 1 < m; i++) {
        edges.push_back({(pts[i] - pts[i + 1]).dist2(), orig_id[i], orig_id[i + 1]});
      }
    } else {
      auto get_id = [&](const P& p) {
        auto it = lower_bound(all(pts), p);
        return orig_id[(int)(it - pts.begin())];
      };
      for (int i = 0; i < sz(tri); i += 3) {
        rep(j, 0, 3) {
          P a = tri[i + j], b = tri[i + (j + 1) % 3];
          edges.push_back({(a - b).dist2(), get_id(a), get_id(b)});
        }
      }
    }
    sort(all(edges));
    for (auto [w, u, v] : edges) {
      if (dsu.join(u, v)) {
        mst_edges.push_back({u, v});
      }
    }
  }

  for (auto [u, v] : mst_edges) {
    cout << u << " " << v << "\n";
  }
}

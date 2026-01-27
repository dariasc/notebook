const ll mod = 998244353;

inline ll mod_plus(ll a, ll b) { return (a + b) % mod; }

struct Tag {
  ll b = 1, c = 0;
  ll map(ll x, int l, int r) const {
    return (x * b % mod + c * (r - l) % mod) % mod;
  }
  Tag operator()(Tag nu) const {
    return {
      b * nu.b % mod,
      (c * nu.b + nu.c) % mod
    };
  }
};

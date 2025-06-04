const ll mod = 998244353;

struct Op {
  ll e = 0;
  ll operator()(ll a, ll b) const {
    return (a + b) % mod;
  }
};

using T = array<ll, 2>;
struct Tag {
  T e = {1, 0};
  ll apply(ll x, T u, int l, int r) const {
    return (x * u[0] % mod + u[1] * (r - l) % mod) % mod;
  }
  T operator()(T lz, T u) const {
    return {
      lz[0] * u[0] % mod,
      (lz[1] * u[0] + u[1]) % mod
    };
  }
};

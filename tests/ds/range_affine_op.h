const ll mod = 998244353;

struct Op {
  using T = ll;
  T e = 0;
  T operator()(T a, T b) const {
    return (a + b) % mod;
  }
};

struct Tag {
  using U = array<ll, 2>;
  U e = {1, 0};
  ll apply(ll x, U u, int l, int r) const {
    return (x * u[0] % mod + u[1] * (r - l) % mod) % mod;
  }
  U operator()(U lz, U u) const {
    return {
      lz[0] * u[0] % mod,
      (lz[1] * u[0] + u[1]) % mod
    };
  }
};

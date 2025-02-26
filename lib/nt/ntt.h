#include "../template.h"
/* -
name = "NTT"
source = "https://github.com/miguelsotocarlos/cp-fft"
[info]
time = "$O(n log n)$"
- */
// the maximum length of the resulting convolution vector is 2^LG
const int LG = 23;
template<class u, class uu, u p, u root>
struct FFT {
  u r[1+(2<<LG)];
  constexpr u m(u a, u b) {
    uu k = uu(a)*b;
    #define op(g) g*(g*p+2)
    k += u(k) * (op(op(op(op(op(-p)))))) * uu(p);
    #undef op
    return u(k>>(8*sizeof(u)));
  }
  constexpr u red(u k, u a) { return a-k*(a>=k); }
  FFT() {
    u k = r[2<<LG] = -p%p, b=root, e = p>>LG;
    for(; e; e/=2, b=m(b,b)) if(e%2) k=m(k, b);
    for(int i = (2<<LG) - 1; i >= 0; i--) r[i]=red(p, m(r[i+1], k)), i&(i-1)?0:k=m(k,k);
    assert(r[2] != r[3]); assert(r[1] == r[2]);
  }
  vec<ll> cv(const vec<ll> &as, const vec<ll> &bs, u *v) {
    int c=max(sz(as)+sz(bs)-1, 0), n=1;
    assert(c <= (1<<LG));
    u h=u(uu(-p)*-p%p), a=m(h, p/2+1), x, y;
    while(n<c) n*=2, h=red(p, m(h, a));
    rep(i, 0, n)
      v[i] = i<sz(as) ? u(as[i]) : 0,
      v[i+n] = i<sz(bs) ? u(bs[i]) : 0;
    for(auto s:{v,v+n})
    for(int j = n; j >= 2; j--) for(int k=j&-j; k/=2;) rep(i, j-k, j)
      x=s[i], y=s[i-k],
      s[i-k] = red(2*p, x+y),
      s[i] = m(2*p+y-x, r[3*k-j+i]);
    rep(i, 0, n) v[i] = m(v[i], v[i+n]);
    rep(j, 2, n+1) for(int k=1; !(k&j); k*=2) rep(i, j-k, j)
      x = m(v[i], r[3*k+j-i]),
      y = red(2*p, v[i-k]),
      v[i-k]=x+y, v[i]=2*p+y-x;
    rep(i, 0, c) v[i] = red(p, m(v[i], h));
    return vec<ll>(v, v+c);
  }
};
// for modular convolutions modulo 998244353:
vec<ll> conv_small(const vec<ll> &as, const vec<ll> &bs) {
  static uint32_t v[2<<LG];
  static FFT<uint32_t, uint64_t, 998244353, 3> fft;
  return fft.cv(as, bs, v);
}
// for modular convolutions modulo a 62 bit prime:
vec<ll> conv_big(const vec<ll> &as, const vec<ll> &bs) {
  static uint64_t v[2<<LG];
  static FFT<uint64_t, __uint128_t, (1ull<<62)-(18ull<<32)+1, 3> fft;
  return fft.cv(as, bs, v);
}
// for modular convolutions modulo an arbitrary 32-bit modulus:
vec<ll> conv_sunzi(const vec<ll> &v1, const vec<ll> &v2, ll m) {
  const uint64_t inv = 2703402103339935109ull,
    mod1 = (1ull<<62)-(18ull<<32)+1,
    mod2 = (1ull<<62)-(76ull<<32)+1;
  static_assert(__uint128_t(inv)*mod2%mod1 == (-mod1)%mod1);
  static uint64_t v[2<<LG];
  static FFT<uint64_t, __uint128_t, mod1, 3> fft1;
  static FFT<uint64_t, __uint128_t, mod2, 17> fft2;
  auto as=fft1.cv(v1, v2, v), bs=fft2.cv(v1, v2, v);
  rep(i, 0, sz(as)) {
    auto d = fft1.m(mod1+as[i]-bs[i], inv);
    d -= mod1*(d >= mod1); d %= m;
    as[i] = (bs[i] + mod2%m*d)%m;
  }
  return as;
}

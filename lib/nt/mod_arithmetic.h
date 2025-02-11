#include "../template.h"
/* -
name = "Modular Arithmetic"
[info]
- */
const ll mod = 998244353; // use const!
#include "mod_pow.h"
struct Mod {
  ll x;
  Mod(ll x) : x(x % mod) {}
  operator ll() const { return x; }
  Mod operator+(Mod b) { return x + b.x; }
  Mod operator-(Mod b) { return x - b.x + mod; }
  Mod operator*(Mod b) { return x * b.x; }
  Mod operator/(Mod b) { return *this * b.inverse(); }
  Mod pow(ll e) {
    return modpow(x, e);
  }
  Mod inverse() {
    return pow(mod - 2);
  }
};

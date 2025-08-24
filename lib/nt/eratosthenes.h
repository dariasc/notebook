#include "../template.h"
/* -
name = "Sieve of Eratosthenes"
[info]
description = "Prime sieve for generating all primes up to a certain limit."
time = "$\"LIM\"=10^8 approx 0.8s$"
- */
const int LIM = 5'000'000;
bitset<LIM> isprime;
vi eratosthenesSieve(int lim) {
  isprime.set(); isprime[0] = isprime[1] = 0;
  for (int i = 4; i < lim; i += 2) isprime[i] = 0;
  for (int i = 3; i*i < lim; i += 2) if (isprime[i])
    for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
  vi pr;
  rep(i,2,lim) if (isprime[i]) pr.push_back(i);
  return pr;
}

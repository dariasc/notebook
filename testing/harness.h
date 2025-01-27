#include <random>
using namespace std;

using ull = unsigned long long;
using ll = long long;
bool test(ull seed);

template <class T>
ll random(T rd, ll max) {
	return rd() % max;
}


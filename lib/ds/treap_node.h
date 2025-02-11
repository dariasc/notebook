#include "../template.h"
/* -
name = "Treap Node"
[info]
- */
mt19937 rng(chrono::high_resolution_clock::now()
            .time_since_epoch().count());
struct Node {
  Node *l = 0, *r = 0;
  int y, c = 1;
  ll x;
  Node(ll x) : y(int(rng())), x(x) {}
  Node* pull() {
    c = 1;
    if (l) c += l->c;
    if (r) c += r->c;
    return this;
  }
  void push() {}
};

#include "../template.h"
/* -
name = "Li Chao Lazy"
source = "https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/lichaoLazy.cpp"
[info]
time = "Generally $O(log n)$ except range updates $O(log^2 n)$"
- */
struct LiChao {
  const int L = -1e9, R = 1e9;
  struct Line {
    ll a, b;
    ll la, lb; // lazy
    array<int, 2> ch;
    Line(ll a_ = 0, ll b_ = LINF) :
      a(a_), b(b_), la(0), lb(0), ch({-1, -1}) {}
    ll operator ()(ll x) { return a*x + b; }
  };
  vec<Line> ln;
  int ch(int p, int d) {
    if (ln[p].ch[d] == -1) {
      ln[p].ch[d] = ln.size();
      ln.emplace_back();
    }
    return ln[p].ch[d];
  }
  LiChao() { ln.emplace_back(); }
  void prop(int p, int l, int r) {
    if (ln[p].la == 0 and ln[p].lb == 0) return;
    ln[p].a += ln[p].la, ln[p].b += ln[p].lb;
    if (l != r) {
      int pl = ch(p, 0), pr = ch(p, 1);
      ln[pl].la += ln[p].la, ln[pl].lb += ln[p].lb;
      ln[pr].la += ln[p].la, ln[pr].lb += ln[p].lb;
    }
    ln[p].la = ln[p].lb = 0;
  }
  ll query(int x, int p=0, int l=L, int r=R) {
    prop(p, l, r);
    ll ret = ln[p](x);
    if (ln[p].ch[0] == -1 and ln[p].ch[1] == -1) return ret;
    int m = l + (r-l)/2;
    if (x <= m) return min(ret, query(x, ch(p, 0), l, m));
    return min(ret, query(x, ch(p, 1), m+1, r));
  }
  void push(Line s, int p, int l, int r) {
    prop(p, l, r);
    int m = l + (r-l)/2;
    bool L = s(l) < ln[p](l);
    bool M = s(m) < ln[p](m);
    bool R = s(r) < ln[p](r);
    if (M) swap(ln[p].a, s.a), swap(ln[p].b, s.b);
    if (s.b == LINF) return;
    if (L != M) push(s, ch(p, 0), l, m);
    else if (R != M) push(s, ch(p, 1), m+1, r);
  }
  void insert(Line s, int a=L, int b=R, int p=0, int l=L, int r=R) {
    prop(p, l, r);
    if (a <= l and r <= b) return push(s, p, l, r);
    if (b < l or r < a) return;
    int m = l + (r-l)/2;
    insert(s, a, b, ch(p, 0), l, m);
    insert(s, a, b, ch(p, 1), m+1, r);
  }
  void shift(Line s, int a=L, int b=R, int p=0, int l=L, int r=R) {
    prop(p, l, r);
    int m = l + (r-l)/2;
    if (a <= l and r <= b) {
      ln[p].la += s.a, ln[p].lb += s.b;
      return;
    }
    if (b < l or r < a) return;
    if (ln[p].b != LINF) {
      push(ln[p], ch(p, 0), l, m);
      push(ln[p], ch(p, 1), m+1, r);
      ln[p].a = 0, ln[p].b = LINF;
    }
    shift(s, a, b, ch(p, 0), l, m);
    shift(s, a, b, ch(p, 1), m+1, r);
  }
};

/**
 el vasito icpc implementation adapted to kactl template
*/
struct Line {
	P p, q;
	double a;
	Line() {}
	Line(P p, P q) : p(p), q(q), a((q - p).angle()) {}
	bool operator<(Line o) const { return a < o.a; }
};
#define L(a) a.p, a.q
#define PQ(a) (a.q - a.p)
#define ang(a) (a.p - a.q).angle()
vector<P> halfPlaneIntersection(vector<Line> v) {
	sort(all(v));
	ll n = sz(v), q = 1, h = 0;
	const long double eps = 1e-18;
	vector<Line> c(n+2);
	#define I(j, k) lineInter(L(c[j]), L(c[k])).se  
	rep(i, 0, n) {
		while (q < h && sideOf(L(v[i]), I(h, h-1), eps) < 0) h--;
		while (q < h && sideOf(L(v[i]), I(q, q+1), eps) < 0) q++;
		c[++h] = v[i];
		if (q < h && abs(PQ(c[h]).cross(PQ(c[h-1]))) < eps) {
			if (PQ(c[h]).dot(PQ(c[h-1])) <= 0) return {};
			if (sideOf(L(v[i]), c[--h].p, eps) < 0) c[h] = v[i];
		}
	}
	while (q < h - 1 && sideOf(L(c[q]), I(h, h-1), eps) < 0) h--;
	while (q < h - 1 && sideOf(L(c[h]), I(q, q+1), eps) < 0) q++;
	if (h - q <= 1) return {};
	c[++h] = c[q];
	vector<P> s;
	rep(i, q, h) s.pb(I(i, i+1));
	return s;
}

/**
Halfplane intersection, works in O(nlogn)
Status: tested in https://codeforces.com/gym/595381/problem/A
Halfplanes are defined by a vector starting from p with direction pq,
covering the left of this line.
*/
struct Halfplane {
	P p, pq;
    long double angle;
    Halfplane() {}
    Halfplane(const P&a, const P&b){ p = a; pq = b; angle = atan2l(pq.y, pq.x); }
    bool out(const P& r) { return pq.cross(r-p) < -eps; }
    bool operator<(const Halfplane& e) const { return angle < e.angle; }
    friend P inter(const Halfplane& s, const Halfplane& t){
        long double alpha = (t.p-s.p).cross(t.pq)/s.pq.cross(t.pq);
        return s.p + (s.pq*alpha);
    }   
};
vector<P> halfPlaneIntersection(vector<Halfplane>& H) { 
    P box[4] = { P(inf, inf), P(-inf, inf), P(-inf, -inf), P(inf, -inf) };
    rep(i,0,4) { // Add bounding box half-planes.
        Halfplane aux(box[i], box[(i+1) % 4] - box[i]);
        H.push_back(aux);
    }
    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    rep(i,0,sz(H)) {
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) { dq.pop_back(); --len; }
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) { dq.pop_front(); --len; }
        if (len > 0 && fabsl(H[i].pq.cross(dq[len-1].pq)) < eps) {
            if (H[i].pq.dot(dq[len-1].pq) < 0.0) return vector<P>();
            if (H[i].out(dq[len-1].p)) { dq.pop_back(); --len; }
            else continue;
        }
        dq.push_back(H[i]);
        ++len;
    }
    while (len>2 && dq[0].out(inter(dq[len-1],dq[len-2]))) { dq.pop_back(); --len; }
    while (len>2 && dq[len-1].out(inter(dq[0],dq[1]))) { dq.pop_front(); --len; }
    if (len<3) return vector<P>();
    vector<P> ret(len);
    rep(i,0,len-1) { ret[i] = inter(dq[i], dq[i+1]); }
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}

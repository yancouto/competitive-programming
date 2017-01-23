#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

#define temp template<typename num>
#define ptn point<num>

temp struct point {
	num x, y;
	ptn() {}
	ptn(num a, num b) : x(a), y(b) {}
	ptn operator + (ptn o) const { return ptn(x + o.x, y + o.y); }
	ptn operator - (ptn o) const { return ptn(x - o.x, y - o.y); }
	num operator * (ptn o) const { return x * o.x + y * o.y; }
	num operator ^ (ptn o) const { return x * o.y - y * o.x; }
	ptn operator * (num i) const { return ptn(x * i, y * i); }
	num dist_sqr(ptn o) const { return (*this - o) * (*this - o); }
};
typedef point<double> ptd;
typedef point<ll> pt;
temp num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }

const double eps = 1e-6;
bool between_seg(ptd a, ptd b, ptd c) {
	return ((b - c) * (a - c)) < -eps;
}


pt p[10];
ll lm, lg;

//ptd proj(ptd a, ptd b, ptd c) {
//	ptd u = c - a;
//	ptd v = b - a;
//	return a + v * ((u * v) / (v * v));
//}
//
//bool okbk(ptd a, ptd b, ptd c) {
//	ptd x = proj(a, b, c);
//	if(x.dist_sqr(c) <= lm * lm + eps && x.dist_sqr(a) <= lg * lg + eps && x.dist_sqr(b) <= lg * lg + eps) return true;
//	if(x.dist_sqr(c) <= lg * lg + eps && !between_seg(a, b, x) && x.dist_sqr(a) <= lm * lm + eps && x.dist_sqr(b) <= lm * lm + eps) return true;
//	return false;
//}

bool ok(pt a, pt b, pt c) {
	pt u = c - a;
	pt v = b - a;
	pt w = c - b;
	pt z = a - b;
	ll nuu = u * u, nvv = v * v;
	ll nuv = u * v;
	ll nww = w * w, nzz = z * z;
	ll nwz = w * z;
	if(
		nuv * nuv <= lg * lg * nvv &&// dx <= lg
		nuu * nvv <= lm * lm * nvv + nuv * nuv &&//dy <= lm
		nwz * nwz <= lg * lg * nzz) return true;
	
	if(
		(nuv <= 0 || nwz <= 0) &&
		nuv * nuv <= lm * lm * nvv &&// dx <= lm
		nuu * nvv <= lg * lg * nvv + nuv * nuv &&//dy <= lg
		nwz * nwz <= lm * lm * nzz) return true;
	return false;
}


int main() {
	int i, j, t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld %lld", &lm, &lg);
		for(i = 0; i < 3; i++) scanf("%lld %lld", &p[i].x, &p[i].y);
		if(cross(p[0], p[1], p[2]) == 0) {
			ll d1 = p[0].dist_sqr(p[1]), d2 = p[0].dist_sqr(p[2]), d3 = p[1].dist_sqr(p[2]);
			if(max(max(d1, d2), d3) <= lm * lm) { puts("YES"); continue; }
			if(max(max(d1, d2), d3) <= 4ll * lg * lg) { puts("YES"); continue; }
		}
		if(ok(p[0], p[1], p[2]) || ok(p[0], p[2], p[1]) || ok(p[1], p[2], p[0])) puts("YES");
		else puts("NO");
	}
}

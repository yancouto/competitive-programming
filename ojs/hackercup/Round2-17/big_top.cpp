#include <bits/stdc++.h>
using namespace std;
#define x first
#define h second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

set<pii> s;
double cur;
const int N = 812345;
ll x[N], h[N];
const double s2 = sqrt(2.);

// assumes no other with p.x
inline void around(pii p, pii &l, pii &r) {
	auto it = s.lower_bound(p);
	if(it == s.end() || it->x - it->h >= p.x + p.h) r.x = -1;
	else r = *it;
	if(it == s.begin() || prev(it)->x + prev(it)->h <= p.x - p.h) l.x = -1;
	else l = *prev(it);
}

double area_with(pii p) {
	pii l, r; around(p, l, r);
	if(l.x == -1 && r.x == -1) return p.h * p.h;
	if(r.x == -1) {
		swap(l, r);
		r.x = p.x + (p.x - r.x);
	}
	double ir = (p.h - r.h + (r.x - p.x)) / 2.;
	double sr = ir * s2;
	if(l.x == -1) {
		//puts("here");
		double sl = (p.h - ir) * s2;
		//printf("ir %.5f\n", ir);
		//printf("sl %.5f sr %.5f\n", sl, sr);
		return sr * sl + sr * sr / 2.;
	} else {
		double sl = ((p.x - l.x) - (l.h - p.h + (p.x - l.x)) / 2.) * s2;
		return sl * sr;
	}
}

void rem(pii p) {
	auto it = s.lower_bound(pii(p.x, LLONG_MIN));
	assert(it != s.end() && it->x == p.x && it->h == p.h);
	s.erase(it);
	cur = cur - area_with(p);
}

void add(int i) {
	auto it = s.lower_bound(pii(x[i], LLONG_MIN));
	if(it != s.end() && it->x == x[i]) {
		if(it->h >= h[i]) return;
		rem(*it);
	}
	pii p(x[i], h[i]);
	pii l, r; around(pii(x[i], h[i]), l, r);
	if(l.x != -1 && l.h - (x[i] - l.x) >= h[i]) return;
	if(r.x != -1 && r.h - (r.x - x[i]) >= h[i]) return;
	while(true) {
		it = s.lower_bound(pii(x[i], LLONG_MIN));
		if(it != s.end() && h[i] - (it->x - x[i]) >= it->h) rem(*it);
		else break;
	}
	while(true) {
		it = s.lower_bound(pii(x[i], LLONG_MIN));
		if(it == s.begin()) break;
		it = prev(it);
		if(h[i] - (x[i] - it->x) >= it->h) rem(*it);
		else break;
	}
	//printf("add %.10f\n", area_with(p));
	cur = cur + area_with(pii(x[i], h[i]));
	s.insert(pii(x[i], h[i]));
}

int main() {
	int i, n;
	ll ax, bx, cx, ah, bh, ch;
	for_tests(tn, tt) {
		scanf("%d %lld %lld %lld %lld %lld %lld %lld %lld", &n, &x[0], &ax, &bx, &cx, &h[0], &ah, &bh, &ch);
		for(i = 1; i < n; i++) {
			x[i] = (((x[i - 1] * ax) + bx) % cx) + 1;
			h[i] = (((h[i - 1] * ah) + bh) % ch) + 1;
		}
		s.clear();
		cur = 0;
		double ans = 0;
		for(i = 0; i < n; i++) {
			//printf("add (%lld, %lld)\n", x[i], h[i]);
			add(i);
			//printf("cur %.10f\n", cur);
			ans += cur;
		}
		printf("Case #%d: %.10f\n", tt, ans);
	}
}

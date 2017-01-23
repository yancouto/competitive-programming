#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }


#include <cmath>
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
	ptn operator / (num i) const { return ptn(x / i, y / i); }
	point<double> rotate(double deg) {
		double cs = cos(deg), sn = sin(deg);
		return point<double>(x*cs - y*sn, x*sn + y*cs);
	}
	num dist_sqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
typedef point<double> ptd;
temp int sign(num x) { return (x > 0) - (x < 0); }

temp struct line {
	num a, b, c;
	line() {}
	line(num aa, num bb, num cc) : a(aa), b(bb), c(cc) {}
	line(ptn s, ptn e) : a(e.y - s.y), b(s.x - e.x), c(a*s.x + b*s.y) {}
	line pass(ptn p) { return line(a, b, a*p.x + b*p.y); }
	bool parallel(const line &o) const { return a * o.b - o.a * b == 0; }
	point<double> inter(line o) {
		double d = a * o.b - o.a * b;
		if(d == 0) return point<double>(0, 0); // fudeu
		return point<double>((o.b * c - b * o.c)/d, (a * o.c - o.a * c)/d);
	}
};
typedef line<int> lni;
typedef line<double> lnd;

ptd p[112];
vector<int> in[112];
vector<pii> rect;
int n;

int go(vector<int> &vs) {
	vector<int> ct;
	for(int g = 0; g < rect.size(); g++) ct.pb(0);
	for(int i : vs)
		for(int x : in[i])
			ct[x]++;
	return *max_element(ct.begin(), ct.end());
}

int go1(int i) {
	vector<int> v; v.pb(i);
	vector<int> v2;
	for(int j = 0; j < n; j++)
		if(i != j)
			v2.pb(j);
	return go(v) + go(v2);
}

int go2(int i, int j) {
	vector<int> v, v2;
	ptd c = (p[i] + p[j]) / 2.;
	double r2 = c.dist_sqr(p[i]);
	for(int g = 0; g < n; g++)
		if(p[g].dist_sqr(c) <= r2 + 1e-6) v.pb(g);
		else v2.pb(g);
	return go(v) + go(v2);
}

int go3(int i, int j, int k) {
	vector<int> v, v2;
	ptd c1 = (p[i] + p[j]) / 2., c2 = (p[j] + p[k]) / 2.;
	ptd a = (p[j] - p[i]);
	swap(a.x, a.y); a.x = -a.x;
	a = a + p[i];
	ptd b = (p[k] - p[j]);
	swap(b.x, b.y); b.x = -b.x;
	b = b + p[j];
	lnd l1(p[i], a), l2(p[j], b);
	l1 = l1.pass(c1); l2 = l2.pass(c2);
	ptd c = l1.inter(l2);
	double r2 = c.dist_sqr(p[i]);
	for(int g = 0; g < n; g++)
		if(p[g].dist_sqr(c) <= r2 + 1e-6) v.pb(g);
		else v2.pb(g);
	return go(v) + go(v2);
}

int main() {
	int i, j, k, r;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &r);
		for(i = 0; i < n; i++) scanf("%lf %lf", &p[i].x, &p[i].y);
		rect.clear();
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				rect.pb(pii(min(p[i].x,p[j].x), min(p[i].y, p[j].y)));
		sort(rect.begin(), rect.end());
		rect.erase(unique(rect.begin(), rect.end()), rect.end());
		for(i = 0; i < n; i++) in[i].clear();
		for(i = 0; i < rect.size(); i++)
			for(j = 0; j < n; j++)
				if(p[j].x >= rect[i].fst && p[j].x <= rect[i].fst + r &&
					p[j].y >= rect[i].snd && p[j].y <= rect[i].snd + r)
					in[j].pb(i);
		int r = 0;
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++)
				for(k = j + 1; k < n; k++)
					r = max(r, go3(i, j, k));
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++)
				r = max(r, go2(i, j));
		for(i = 0; i < n; i++)
			r = max(r, go1(i));
		printf("Case #%d: %d\n", tt, r);
	}
}

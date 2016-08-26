#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, double> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

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
	num distSqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
typedef point<int> pti;
typedef point<double> ptd;
const int N = 160009;
pti pi[N], st[N];
ptd p[N];
int sn;

pii tern(int l, int r, function<double(ptd)> f) {
	while(r - l > 10) {
		int m = (l + r) / 2;
		if(f(p[m + 2]) >= f(p[m - 2])) l = m - 2;
		else r = m + 2;
	}
	int b = l;
	for(l++; l <= r; l++)
		if(f(p[l]) > f(p[b]))
			b = l;
	return pii(b, f(p[b]));
}

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d", &pi[i].x, &pi[i].y);
	sort(pi, pi + n);
	for(i = 0; i < n; i++) {
		while(sn >= 2 && cross(st[sn - 2], st[sn - 1], pi[i]) >= 0)
			sn--;
		st[sn++] = pi[i];
	}
	int k = sn;
	for(i = n - 2; i >= 0; i--) {
		while(sn >= k + 1 && cross(st[sn - 2], st[sn - 1], pi[i]) >= 0)
			sn--;
		st[sn++] = pi[i];
	}
	sn--;
	for(i = 0; i < 2*sn; i++)
		p[i] = ptd(st[i%sn].x, st[i%sn].y);
	n = sn;
	double mn = 1/0.;
	ptd q0[4];
	for(i = 0; i < n; i++) {
		ptd a = p[i], b = p[i + 1];
		ptd c = b - a; double ang = atan2(c.y, c.x);
		auto op = [=](ptd p) { return (p - a).rotate(-ang); };
		pii my = tern(i, i + n, [=](ptd p) { return op(p).y; });
		double y0 = 0;
		double y1 = my.snd;
		double x0 = tern(my.fst, i + n, [=](ptd p) { return -op(p).x; }).snd;
		double x1 = tern(i, my.fst, [=](ptd p) { return op(p).x; }).snd;
		ptd q[4];
		q[0] = ptd(x0, y0);
		q[1] = ptd(x1, y0);
		q[2] = ptd(x1, y1);
		q[3] = ptd(x0, y1);
		if(y1 * (x1 - x0) < mn) {
			mn = y1 * (x1 - x0);
			for(int j = 0; j < 4; j++) q0[j] = (q[j].rotate(ang) + a);
		}
	}
	for(i = 0; i < 4; i++)
		printf("%.10f %.10f\n", q0[i].x, q0[i].y);
}

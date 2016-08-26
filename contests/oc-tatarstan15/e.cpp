#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
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
	bool operator < (ptn o) const  { return x < o.x || (x == o.x && y < o.y); }
};
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }

typedef point<ll> pti;
typedef point<double> ptd;

pti pi[80009];
pti st[80009];
ptd p[160009];

double tern(int l, int r, function<double(int)> f) {
	while(r - l > 4) {
		int m = (l + r) / 2;
		if(f(m + 1) >= f(m - 1)) l = m;
		else r = m;
	}
	double mx = -1/0.;
	for(int i = l; i <= r; i++)
		mx = max(mx, f(i));
	return mx;
}

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lld %lld", &pi[i].x, &pi[i].y);
	sort(pi, pi + n);
	j = 0;
	for(i = 0; i < n; i++)
		if(i == n - 1 || pi[i].x != pi[i+1].x || pi[i].y != pi[i+1].y)
			pi[j++] = pi[i];
	n = j;
	sort(pi + 1, pi + n, [](pti a, pti b) {
		if(cross(pi[0], a, b) != 0)
			return cross(pi[0], a, b) < 0;
		if(a.x == pi[0].x) return a.y > b.y;
		return a.distSqr(pi[0]) < b.distSqr(pi[0]);
	});
	int sn = 0;
	st[sn++] = pi[0];
	st[sn++] = pi[1];
	for(i = 2; i < n; i++) {
		while(sn >= 2 && cross(st[sn - 2], st[sn - 1], pi[i]) >= 0)
			sn--;
		st[sn++] = pi[i];
	}
	while(sn >= 2 && cross(st[sn - 2], st[sn - 1], st[0]) == 0) sn--;
	//for(i = 0; i < sn; i++)
	//	printf("%lld, %lld\n", st[i].x, st[i].y);
	for(i = 0; i < 2 * sn; i++)
		p[i] = ptd(st[i%sn].x, st[i%sn].y);
	n = sn;
	double ar = 1/0.;
	ptd q0[4];
	for(i = 0; i < n; i++) {
		ptd a = p[i], b = p[i + 1];
		ptd x = b - a;
		double ang = atan2(x.y, x.x);
		//printf("x %.0f %.0f\n", x.x, x.y);
		//printf("ang = %.10f\n", ang);
		auto op = [=](ptd p) { return (p - a).rotate(-ang); };
		double px[2], py[2];
		py[0] = 0;
		py[1] = tern(i + 1, i + n - 1, [=](int i) { return op(p[i]).y; });
		px[0] = tern(i + 1, i + n, [=](int i) { return -op(p[i]).x; });
		px[1] = tern(i + 1, i + n - 1, [=](int i) { return op(p[i]).x; });
		ptd q[4];
		//printf("on %d quad is %.2f->%.2f %.2f->%.2f\n", i, py[0], py[1], px[0], px[1]);
		q[0] = ptd(px[0], py[0]);
		q[1] = ptd(px[1], py[0]);
		q[2] = ptd(px[1], py[1]);
		q[3] = ptd(px[0], py[1]);
		if(py[1] * (px[1] - px[0]) < ar) {
			ar = py[1] * (px[1] - px[0]);
			//for(j = 0; j < 4; j++) printf("q[%d] = %.2f, %.2f\n", j, q[j].x, q[j].y);
			for(j = 0; j < 4; j++) q0[j] = (q[j].rotate(ang) + a);
			//for(j = 0; j < 4; j++) printf("q0[%d] = %.2f, %.2f\n", j, q0[j].x, q0[j].y);
		}
	}
	for(i = 0; i < 4; i++)
		printf("%.10f %.10f\n", q0[i].x, q0[i].y);
}

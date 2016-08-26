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
	num dist_sqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
typedef point<int> pti;
typedef point<double> ptd;

temp struct line {
	num a, b, c;
	line() {}
	line(num aa, num bb, num cc) : a(aa), b(bb), c(cc) {}
	line(ptn s, ptn e) : a(e.y - s.y), b(s.x - e.x), c(a*s.x + b*s.y) {}
	bool parallel(const line &o) const { return a * o.b - o.a * b == 0; }
	point<double> inter(line o) {
		double d = a * o.b - o.a * b;
		if(d == 0) return point<double>(0, 0); // fudeu
		return point<double>((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
};
typedef line<double> lnd;

const double eps = 1e-5;
const int N = 11234;

pti pi[N][3];
ptd p[N][3], a[N];
double r[N];

int main() {
	int i, n, j, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		for(j = 0; j < 3; j++) {
			scanf("%d %d", &pi[i][j].x, &pi[i][j].y);
			p[i][j] = ptd(pi[i][j].x, pi[i][j].y);
		}
		lnd l[2];
		for(j = 0; j < 2; j++) {
			ptd v = p[i][j + 1] - p[i][j];
			v = ptd(-v.y, v.x);
			ptd mid = (p[i][j + 1] + p[i][j]) / 2.;
			l[j] = lnd(mid, mid + v);
		}
		a[i] = l[0].inter(l[1]);
		r[i] = a[i].dist_sqr(p[i][0]);
		//assert(abs(r[i] - a[i].dist_sqr(p[i][1])) <= eps);
		//assert(abs(r[i] - a[i].dist_sqr(p[i][2])) <= eps);
	}
	for(i = 0; i < n; i++) {
		set<pti> s; s.insert(pi[i][0]); s.insert(pi[i][1]); s.insert(pi[i][2]);
		for(j = 0; j < n; j++)
			for(k = 0; k < 3; k++) {
				if(s.count(pi[j][k])) continue;
				if(a[i].dist_sqr(p[j][k]) < r[i] - eps) { puts("NO"); return 0; }
			}
	}
	puts("YES");
}

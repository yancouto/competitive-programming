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
	num operator ^ (ptn o) const { return x * o.y - y * o.x; }
	ptn operator * (num i) const { return ptn(x * i, y * i); }
	ptn operator / (num i) const { return ptn(x / i, y / i); }
	double norm() const { return sqrt(x * x + y * y); }
};
typedef point<int> pti;
typedef point<double> ptd;

temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }

temp int sign(num x) { return (x > 0) - (x < 0); }

temp struct line {
	num a, b, c;
	line() {}
	line(num aa, num bb, num cc) : a(aa), b(bb), c(cc) {}
	line(ptn s, ptn e) : a(e.y - s.y), b(s.x - e.x), c(a * s.x + b * s.y) {}
	line pass(ptn p) { return line(a, b, a * p.x, b * p.y); }
	point<double> inter(line o) {
		double d = a * o.b - o.a * b;
		return point<double>((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
};
typedef line<double> lnd;

int n, m, N;
ptd p[1123];
int pe[1123];
const double eps = 1e-6;

void go(ptd a, double d) {
	int s = -1;
	for(int i = 0; i < N; i++) {
		swap(pe[i], pe[i + (rand() % (N - i))]);
		ptd k = p[pe[i]];
		if(abs((k - a).norm() - d) <= eps) continue;
		bool in = ((k - a).norm() <= d);
		//printf("s %d in %d pe[%d] = %d\n", s, in, i, pe[i]);
		if(s == -1) { s = (in != (pe[i] < n)); continue; }
		if(s != (in != (pe[i] < n))) return;
	}
	printf("YES\n%.10f %.10f %.10f\n", a.x, a.y, d);
	exit(0);
}

void center(ptd a, ptd b, ptd c) {
	ptd ab = (a + b) / 2.;
	ptd bc = (b + c) / 2.;
	ptd vab = (b - a);
	ptd vbc = (c - b);
	swap(vab.x, vab.y); vab.x = -vab.x;
	swap(vbc.x, vbc.y); vbc.x = -vbc.x;
	ptd ce = lnd(ab, ab + vab).inter(lnd(bc, bc + vbc));
	go(ce, (ce - a).norm());
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("wall.in", "r", stdin);
	freopen("wall.out", "w", stdout);
#endif
	int i, j, k;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) scanf("%lf %lf", &p[i].x, &p[i].y);
	for(i = 0; i < m; i++) scanf("%lf %lf", &p[i + n].x, &p[i + n].y);
	N = n + m;
	for(i = 0; i < N; i++) pe[i] = i;
	for(i = 0; i < n + m; i++)
		for(j = i + 1; j < n + m; j++)
			go((p[i] + p[j]) / 2., (p[j] - p[i]).norm() / 2.);
	for(i = 0; i < n + m; i++)
		for(j = i + 1; j < n + m; j++)
			for(k = j + 1; k < n + m; k++)
				if(cross(p[i], p[j], p[k]))
					center(p[i], p[j], p[k]);
	puts("NO");
}

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

int n;
const double eps = 1e-9, pi = acos(-1);

inline bool eq(double a, double b) { return abs<double>(a - b) <= eps; }
inline double sq(double a) { return a * a; }

const int N = 1123;

bool bad[N];
double x[N], y[N], l[N];


int stable_or_imp(double x, double y) {
	bool lb = false, r = false;
	for(int i = 0; i < n; i++) {
		if(bad[i]) continue;
		if(eq(x, ::x[i]) && y - l[i] >= -eps) return 1;
		if(::x[i] - x <= eps  && y - l[i] >= -eps) lb = true;
		if(::x[i] - x >= -eps && y - l[i] >= -eps) r = true;
	}
	if(lb && r) return 2;
	return 0;
}


double angr(double x, double y) {
	return atan2(y, x);
}


double rotate(double &x, double &y, double ang) {
	double cs = cos(ang), sn = sin(ang);
	double nx = cs * x - sn * y;
	y = cs * x + sn * y;
	x = nx;
}

void go(double &x, double &y) {
	if(n == 1) {
		x = ::x[0];
		y = l[0];
		return;
	}
	y = -100;
	for(int i = 0; i < n; i++)
		for(int j = i + 1; j < n; j++) {
			double tx = l[i] + l[j] + sq(::x[j]) - sq(::x[i]);
			tx /= 2. * (::x[j] - ::x[i]);
			double ty = sqrt(sq(l[i]) - sq(tx - ::x[i]));
			int ok = 1;
			for(int k = 0; k < n && ok; k++)
				if(sq(tx - ::x[k]) + sq(ty - ::y[k]) > sq(l[k]))
					ok = 0;
			if(ok && ty > y)
				x = tx, y = ty;
		}
}

int p[N];
double t[N];
int main() {
	int i, j, k, m;
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) scanf("%lf", &x[i]);
	for(i = 0; i < n; i++) scanf("%lf", &l[i]);
	for(i = 0; i < n; i++) scanf("%d", &p[i]), p[i]--;
	for(i = 0; i < m; i++) scanf("%lf", &t[i]);
	int ti = 0;
	double x, y; // parte do sena
	go(x, y);
	double cur = 0;
	for(i = 0; i < n; i++) {
		bad[p[i]] = true;
		if(stable_or_imp(x, y)) continue;
		if(eq(::x[p[i]], x)) {
			double l = y, r = 10000;
			for(int g = 0; g < 100; g++) {
				double m = (l + r) / 2;
				if(stable_or_imp(x, m)) l = m;
				else r = m;
			}
			while(ti < m && t[ti] - cur <= l - y) printf("%.10f %.10f\n", x, -(y + (t[ti] - cur))), ti++;
			cur += l - y;
			y = l;
		} else if(x > ::x[p[i]]) {
			double l = 0, r = pi / 2. - angr(x, y);
			for(int g = 0; g < 100; g++) {
				double m = (l + r) / 2;
				double x2 = x, y2 = y;
				rotate(x2, y2, m);
				if(stable_or_imp(x2, y2)) l = m;
				else r = m;
			}
			while(ti < m && t[ti] - cur <= l * ::l[p[i]]) {
				double x2 = x, y2 = y;
				rotate(x2, y2, double(t[ti] - cur) / ::l[p[i]]);
				printf("%.10f %.10f\n", x2, -y2);
				ti++;
			}
			cur += l * ::l[p[i]];
			rotate(x, y, l);
		} else {
			double l = 0, r = abs<double>(pi / 2. - angr(x, y));
			for(int g = 0; g < 100; g++) {
				double m = (l + r) / 2;
				double x2 = x, y2 = y;
				rotate(x2, y2, -m);
				if(stable_or_imp(x2, y2)) l = m;
				else r = m;
			}
			while(ti < m && t[ti] - cur <= l * ::l[p[i]]) {
				double x2 = x, y2 = y;
				rotate(x2, y2, -double(t[ti] - cur) / ::l[p[i]]);
				printf("%.10f %.10f\n", x2, -y2);
				ti++;
			}
			cur += l * ::l[p[i]];
			rotate(x, y, -l);
		}
	}
	while(ti < m) {
		printf("%.10f %.10f\n", x, -(y + t[ti] - cur));
		ti++;
	}
}

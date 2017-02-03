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

typedef long double ld;
#define double ld

int n;
const double eps = 5e-9, pi = acos(-1);

inline bool eq(double a, double b, const double eps) { return abs<double>(a - b) <= eps; }
inline bool le(double a, double b, const double eps) { return a - b <= eps; }
inline bool lt(double a, double b, const double eps) { return a - b <= -eps; }
inline double sq(double a) { return a * a; }

const int N = 1123;

bool bad[N];
double x[N], y[N], l[N];

int ql, qr;
int state(double x, double y, const double eps) {
	int ret = 0; ql = qr = -1;
	for(int i = 0; i < n; i++) {
		if(bad[i]) continue;
		if(lt(l[i], sqrt(sq(x - ::x[i]) + sq(y)), eps)) return -1;
		if(le(x, ::x[i], eps) && eq(l[i], sqrt(sq(y) + sq(x - ::x[i])), eps)) {
			ret |= 1;
			if(qr == -1 || l[qr] > l[i])
				qr = i;
		}
		if(le(::x[i], x, eps) && eq(l[i], sqrt(sq(y) + sq(x - ::x[i])), eps)) {
			ret |= 2;
			if(ql == -1 || l[ql] > l[i])
				ql = i;
		}
	}
	return ret;
}


double angr(double x, double y) {
	return atan2<double>(y, x);
}


double rotate(double &x, double &y, double ang) {
	double cs = cos(ang), sn = sin(ang);
	double nx = cs * x - sn * y;
	y = sn * x + cs * y;
	x = nx;
}

void go(double &x, double &y) {
	x = y = 0;
	for(int i = 0; i < n; i++) {
		if(lt(x, ::x[i] - l[i], eps)) x = ::x[i] - l[i];
		if(lt(::x[i] + l[i], x, eps)) x = ::x[i] + l[i];
	}
	//printf(">>%.5f,%.5f<<\n", x, y);
}
int p[N], ti, m;
double t[N];

void stabilize(double &x, double &y, double &cur) {
	int mx = 0, j;
	while(state(x, y, eps) != 3 && mx++ < 23) {
		state(x, y, eps);
		//printf("(%.2f, %.2f) %d\n", x, y, state(x, y, eps));
		if(ql == -1 && qr == -1) {
			assert(state(x, y, eps / 5) == 0);
			double l = y, r = 10000;
			for(int g = 0; g < 100; g++) {
				double m = (l + r) / 2;
				if(state(x, m, eps / 5) == 0) l = m;
				else r = m;
			}
			while(ti < m && t[ti] - cur <= l - y) (cout << x << ' ' << -(y + (t[ti] - cur)) << '\n'), ti++;
			cur += l - y;
			y = l;
		} else if(ql != -1) {
			int k = ql;
			assert(state(x, y, eps) == 2);
			//puts("hhhhhh");
			x -= ::x[k];
			double mt = l[k] / sqrt(sq(y) + sq(x));
			x *= mt;
			y *= mt;
			x += ::x[k];
			if(state(x, y, eps / 5) != 2) { mx--; continue; }
			double l = 0, r = pi / 2. - angr(x - ::x[k], y);
			for(int g = 0; g < 100; g++) {
				double m = (l + r) / 2;
				double x2 = x - ::x[k], y2 = y;
				rotate(x2, y2, m);
				if(state(x2 + ::x[k], y2, eps / 5) == 2) l = m;
				else r = m;
			}
			l = r;
			while(ti < m && t[ti] - cur <= l * ::l[k]) {
				double x2 = x - ::x[k], y2 = y;
				rotate(x2, y2, double(t[ti] - cur) / ::l[k]);
				cout << x2 + ::x[k] << " " << -y2 << '\n';
				ti++;
			}
			cur += l * ::l[k];
			x -= ::x[k];
			rotate(x, y, l);
			x += ::x[k];
		} else {
			int k = qr;
			assert(state(x, y, eps) == 1);
			//puts("asdasdasd");
			x -= ::x[k];
			double mt = l[k] / sqrt(sq(y) + sq(x));
			x *= mt;
			y *= mt;
			x += ::x[k];
			if(state(x, y, eps / 5) != 1) { mx--; continue; }
			double l = 0, r = abs<double>(pi / 2. - angr(x - ::x[k], y));
			//printf("from %.3f to %.3f\n", l, r);
			for(int g = 0; g < 100; g++) {
				double m = (l + r) / 2;
				double x2 = x - ::x[k], y2 = y;
				rotate(x2, y2, -m);
				//if((g % 20) == 0 || g < 5) printf("[%.4f---%.4f]\n", l, r);
				//if((g % 20) == 0 || g < 5) printf("[%.4f]state(%.4f, %.4f) = %d\n", m, x2 + ::x[k], y2, state(x2 + ::x[k], y2, eps/10));
				if(state(x2 + ::x[k], y2, eps / 5) == 1) l = m;
				else r = m;
			}
			l = r;
			while(ti < m && t[ti] - cur <= l * ::l[k]) {
				double x2 = x - ::x[k], y2 = y;
				rotate(x2, y2, -double(t[ti] - cur) / ::l[k]);
				cout << x2 + ::x[k] << " " << -y2 << '\n';
				ti++;
			}
			//printf("chose %.3f\n", l);
			cur += l * ::l[k];
			x -= ::x[k];
			rotate(x, y, -l);
			x += ::x[k];
		}
	}

}

int main() {
	int i, j, k;
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cout.precision(15);
	cin >> n >> m;
	for(i = 0; i < n; i++) cin >> x[i];
	for(i = 0; i < n; i++) cin >> l[i];
	for(i = 0; i < n - 1; i++) (cin >> p[i]), p[i]--;
	for(i = 0; i < m; i++) cin >> t[i];
	ti = 0;
	double x, y;
	go(x, y);
	double cur = -100000;
	stabilize(x, y, cur);
	cur = 0;
	//printf(">> %.10f %.10f\n", x, y);
	for(i = 0; i < n - 1; i++) {
		bad[p[i]] = true;
		stabilize(x, y, cur);
	}
	while(ti < m) {
		cout << x << ' ' << -y << '\n';
		ti++;
	}
}

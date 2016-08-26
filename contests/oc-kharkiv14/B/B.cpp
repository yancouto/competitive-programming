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
const int N = 112345;
#define double long double
const double pi = acos(-1);
const double eps = 1e-9;

int a[N];
int n;
inline double sqr(double x) { return x * x; }

bool ok(double r) {
	double ang = 0;
	for(int i = 0; i < n && ang <= 2.* pi + .1; i++) {
		double s = a[i] / (2. * r);
		double al = 2. * atan2(a[i] / 2., sqrt(r * r - (sqr(a[i]) / 4.)));
		ang += al;
	}
	if(ang <= 2. * pi) return true;
	else return false;
}

double X[N], Y[N];

int main(int argn, char **args) {
	if(argn>1) srand(atoi(args[1]));
	clock_t c = clock();
	int i;
	scanf("%d", &n);
	ll tot = 0;
	for(i = 0; i < n; i++) {
		//scanf("%d", &a[i]);
		a[i] = (rand() % 100000) + 1;
		tot += a[i];
	}
	if(2ll*(*max_element(a, a + n)) >= tot) { puts("Impossible"); return 0; }
	double l = (double)(*max_element(a, a + n)) / 2., r = 1e10;
	while((double)(clock() - c) / CLOCKS_PER_SEC < 4.6) { 
		double m = (l + r) / 2;
		if(ok(m)) r = m;
		else l = m;
	}
	r = (l + r) / 2.;
	double x = r, y = 0; 
	double ang = 0;
	for(i = 0; i < n; i++) {
		X[i] = x; Y[i] = y;
		assert(abs(x) <= 2e9 + 4 && abs(y) <= 2e9 + 3);
		//printf("%.10Lf %.10Lf\n", x, y);
		double s = a[i] / (2. * r);
		double al = 2. * atan2(a[i] / 2., sqrt(r * r - (sqr(a[i]) / 4.)));
		ang += al;
		//double c = sqrt(1. - s * s);
		//double cs = c * c - s * s, sn = 2. * s * c;
		double cs = cos(ang), sn = sin(ang);
		
		double ox = r, oy = 0;
		x = ox*cs - oy*sn;
		y = ox*sn + oy*cs;
	}
	X[n] = X[0]; Y[n] = Y[0];
	for(i = 0; i < n; i++)
		assert(abs(sqrt(sqr(X[i + 1] - X[i]) + sqr(Y[i + 1] - Y[i])) - (double)(a[i])) <= 1e-4);
}

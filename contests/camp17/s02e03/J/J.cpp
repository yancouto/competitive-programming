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

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;
const int N = 412;
int x[N];

typedef long double ld;
//#define double ld

double solve(double d, int c) {
	double tot = 0;
	for(int i = 0; i < n; i++)
		tot += abs(x[i] - (x[c] + (i - c) * d));
	return tot;
}

double mid;
double go(int c) {
	double l = 0, r = 20000;
	while(r - l > 1e-9) {
		double m1 = (2.*l + r) / 3.;
		double m2 = (l + 2.*r) / 3.;
		if(solve(m1, c) < solve(m2, c)) r = m2;
		else l = m1;
	}
	mid = (l + r) / 2;
	return solve((l + r) / 2, c);
}

void build(double mn, double md, int c) {
	//cout << setprecision(4) << mn << '\n';
	printf("%.15f\n", mn);
	//double z[N];
	//for(int i = 0; i < n; i++)
	//	z[i] = x[c] + (i - c)  * md;
	//double t = 0;
	//for(int i = 0; i < n; i++)
	//	t += abs(x[i] - z[i]);
	//cout << "ans " << t << '\n';
	for(int i = 0; i < n; i++)
		printf("%.15f ", (x[c] + (i - c) * md));
		//cout << setprecision(7) << (x[c] + (i - c) * md) << ' ';
	putchar('\n');
	//cout << '\n';
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j;
	rd(n);
	for(i = 0; i < n; i++) rd(x[i]);
	double mn = go(0);
	double md = mid;
	int mn_i = 0;
	for(i = 1; i < n; i++) {
		double g = go(i);
		if(g < mn) mn = g, mn_i = i, md = mid;
	}
	build(mn, md, mn_i);
}

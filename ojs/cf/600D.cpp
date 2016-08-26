// WRONG
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
inline ll sq(ll x) { return x * x; }
inline double sqq(double x) { return x * x; }

ll x[2], y[2], r[2];
int main() {
	int i;
	clock_t c = clock();
	for(i = 0; i < 2; i++)
		scanf("%lld %lld %lld", &x[i], &y[i], &r[i]);
	if(sq(x[1] - x[0]) + sq(y[1] - y[0]) >= sq(r[0] + r[1])) { puts("0"); return 0; }
	ll mn_x = max(x[0] - r[0], x[1] - r[1]);
	ll mx_x = min(x[0] + r[0], x[1] + r[1]);
	ll mn_y = max(y[0] - r[0], y[1] - r[1]);
	ll mx_y = min(y[0] + r[0], y[1] + r[1]);
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> disx(mn_x, mx_x);
	uniform_real_distribution<double> disy(mn_y, mx_y);
	double ar = (mx_x - mn_x) * (mx_y - mn_y);
	ll all, in = 0;
	ll r02 = sq(r[0]), r12 = sq(r[1]);
	for(all = 0; double(clock() - c) / CLOCKS_PER_SEC < 1.9; all++) {
		double xx = disx(gen), yy = disy(gen);
		if(sqq(xx - x[0]) + sqq(yy - y[0]) <= r02 && sqq(xx - x[1]) + sqq(yy - y[1]) <= r12)
			in++;
	}
	printf("%.15f\n", (double(in) / all) * ar);
}

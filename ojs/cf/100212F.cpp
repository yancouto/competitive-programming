#include <bits/stdc++.h>
using namespace std;
#define d first
#define i second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<double, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const double pi = acos(-1);
int n, r; double h;
pii x[3][1003];
double dist(double x1, double x2) {
	double d = (x1 - x2) * (x1 - x2);
	d = min(d, (x1 + 2 * pi * r - x2) * (x1 + 2 * pi * r - x2));
	d = min(d, (x1 - 2 * pi * r - x2) * (x1 - 2 * pi * r - x2));
	return sqrt(d + h * h);
}
int rot[2];
double mnf(int g) {
	int i, j;
	double best = 1/0.;
	for(i = 0; i < n; i++) {
		double tot = 0;
		for(j = 0; j < n; j++)
			tot += dist(x[g][j].d, x[g + 1][(j + i) % n].d);
		if(tot < best) rot[g] = i;
		best = min(best, tot);
	}
	return best;
}

int main() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	double al;
	int i, j;
	scanf("%d %d %lf", &n, &r, &h); h /= 2.;
	for(j = 0; j < 3; j++) {
		for(i = 0; i < n; i++) {
			scanf("%lf", &al);
			if(al < 0) al += 2 * pi;
			x[j][i] = pii(al * r, i + 1);
		}
		sort(x[j], x[j] + n);
	}
	printf("%.15f\n", mnf(0) + mnf(1));
	for(i = 0; i < n; i++)
		printf("%d %d %d\n", x[0][i].i, x[1][(rot[0] + i) % n].i, x[2][(i + rot[0] + rot[1]) % n].i);
}

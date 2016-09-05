#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<ld, ld> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 11234;
inline ld sq(ld a) { return a * a; }
ld x[N][2], y[N];
const ld eps = 0;

ld memo[N][2];
int seen[N][2], t, n;
ld solve(int i, int j) {
	ld &r = memo[i][j];
	if(seen[i][j] == t) return r;
	seen[i][j] = t;
	if(i == n - 1) return r = 0;
	r = 1/0.;
	ld a = -100, b = 100;
	bool ok = true;
	for(int k = i + 1; k < n; k++) {
		if(x[k][0] > x[i][j] + eps) ok = false;
		if(x[k][1] < x[i][j] - eps) ok = false;
		for(int g = 0; g < 2; g++) {
			ld f = atan2l(y[k] - y[i], x[k][g] - x[i][j]);
			if(f < a - eps || f > b + eps) continue;
			r = min(r, solve(k, g) + sqrtl(sq(y[k] - y[i]) + sq(x[k][g] - x[i][j])));
			if(g) a = f;
			else b = f;
		}
	}
	if(ok) r = y[n - 1] - y[i];
	return r;
}

ld read() {
	double d;
	scanf("%lf", &d);
	return d;
}

int main() {
	int i;
	while(scanf("%d", &n) != EOF && n) {
		x[0][0] = read(); y[0] = -read(); n++;
		for(i = 1; i < n; i++) {
			y[i] = -read(); x[i][0] = read(); x[i][1] = read();
			assert(x[i][0] <= x[i][1] && y[i] > y[i-1]);
		}
		t++;
		printf("%.25f\n", (double)solve(0, 0));
	}
}

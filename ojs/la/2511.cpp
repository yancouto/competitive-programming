#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
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
ld y[N], x[N][2]; int n;
ld sq(ld x) { return x * x; }

ld dist(pii a, pii b) { return sqrtl(sq(a.x - b.x) + sq(a.y - b.y)); }
ld cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }

pii operator - (pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }

ld myatan(ld y, ld x) {
	ld k = atan2l(y, x);
	assert(k >= 0);
	return k;
}

ld memo[N][2];
int seen[N][2], t;
ld solve(int i, int j) {
	ld &r = memo[i][j];
	if(seen[i][j] == t) return r;
	seen[i][j] = t;
	if(i == n - 1) return r = 0;
	pii p(x[i][j], y[i]);
	ld al = acosl(-1);
	ld ar = 0;
	r = 1/0.;
	for(int k = i + 1; k < n; k++) {
		for(int g = 0; g < 2; g++) {
			assert(y[k] > y[i]);
			pii np(x[k][g], y[k]);
			ld a = myatan(np.y - p.y, np.x - p.x);
			if(a >= ar && a <= al) r = min(r, solve(k, g) + dist(p, np));
			if(g) ar = max(ar, a);
			else al = min(al, a);
		}
	}
	ld a = acosl(-1) / 2.;
	if(a >= ar && a <= al && p.x >= x[n-1][0] && p.x <= x[n-1][1]) r = min(r, y[n - 1] - y[i]);
	return r;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int i;
	while((cin >> n) && n) {
		cin >> x[0][0] >> y[0];
		x[0][1] = x[0][0]; n++;
		for(i = 1; i < n; i++)
			cin >> y[i] >> x[i][0] >> x[i][1];
		for(i = 0; i < n; i++) y[i] = -y[i];
		t++;
		cout << setprecision(25) << solve(0, 0) << '\n';
	}
}

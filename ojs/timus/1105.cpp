#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

struct ob {
	double x, y; int i;
	double d;
	bool operator < (ob o) const {
		if(x != o.x) return x < o.x;
		return y > o.y;
	}
} g[11234], k[11234];

int main() {
	double t0, t1;
	int i, n;
	scanf("%lf %lf %d", &t0, &t1, &n);
	for(i = 0; i < n; i++) {
		scanf("%lf %lf", &g[i].x, &g[i].y);
		g[i].i = i;
	}
	sort(g, g + n);
	int j = 1;
	for(i = 1; i < n; i++) {
		if(g[i].y <= g[j - 1].y) continue;
		g[j++] = g[i];
	}
	n = j;
	j = 1;
	for(i = 1; i < n - 1; i++) {
		if(g[j - 1].y >= g[i + 1].x) continue;
		g[j++] = g[i];
	}
	g[j++] = g[n - 1];
	n = j;
	double tot = 0;
	for(i = 1; i < n; i += 2) tot += g[i].y - g[i].x;
	if(tot >= 2./3. * (t1 - t0)) {
		printf("%d\n", n / 2);
		for(i = 1; i < n; i += 2) printf("%d\n", g[i].i + 1);
		return 0;
	}
	vector<int> v;
	for(i = 0; i < n; i += 2) v.pb(g[i].i + 1);
	g[n].x = t1;
	for(i = 1; i < n; i += 2) {
		k[i / 2] = g[i];
		double l = g[i].y - g[i].x;
		double e = g[i + 1].x - g[i - 1].y;
		k[i / 2].d = 2 * e - l;
	}
	sort(k, k + (n/2), [](ob a, ob b) { return a.d > b.d; });
	for(i = 0; i < n/2 && k[i].d > 0; i++)
		v.pb(k[i].i + 1);
	printf("%d\n", (int) v.size());
	for(int i : v) printf("%d\n", i);
}

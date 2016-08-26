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
const int N = 100009;

int x[N], y[N], w, vh, n;
bool pos(double v) {
	double l = x[0], r = x[0] + w;
	for(int i = 1; i < n; i++) {
		double dx = ((y[i] - y[i - 1]) / v) * vh;
		l -= dx;
		r += dx;
		if(r < x[i] || l > x[i] + w) return false;
		r = min<double>(r, x[i] + w);
		l = max<double>(l, x[i]);
	}
	return true;
}

int v[1000009];
int main() {
	int i, s;
	scanf("%d %d %d", &w, &vh, &n);
	for(i = 0; i < n; i++) 
		scanf("%d %d", &x[i], &y[i]);
	scanf("%d", &s);
	for(i = 0; i < s; i++)
		scanf("%d", &v[i]);
	sort(v, v + s);
	if(!pos(v[0])) { puts("IMPOSSIBLE"); return 0; }
	int l = 0, r = s - 1;
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(pos(v[m])) l = m;
		else r = m - 1;
	}
	printf("%d\n", v[l]);
}

#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

struct point {
	int x, y;
} ps[3009];

int mt[3010][3010];
map<int, int> mpx, mpy;

int get(int x1, int y1, int x2, int y2) {
	int xl = mpx.lower_bound(x1)->snd;
	int xr = prev(mpx.upper_bound(x2))->snd;
	int yl = mpy.lower_bound(y1)->snd;
	int yr = prev(mpy.upper_bound(y2))->snd;
	int v = mt[xr][yr] - mt[xl-1][yr] - mt[xr][yl-1] + mt[xl-1][yl-1];
	return v;
}

int main() {
	int i, j, n, k, x, y, q;
	scanf("%d", &n);
	mpx[INT_MIN] = mpx[INT_MIN+1] = mpy[INT_MIN] = mpy[INT_MIN+1] = 0;
	mpx[INT_MIN + 2] = mpy[INT_MIN + 2] = 0;
	for(i = 0; i < n; i++) {
		scanf("%d %d", &ps[i].x, &ps[i].y);
		mpx[ps[i].x] = mpy[ps[i].y] = 0;
	}
	i = 0;
	for(auto &e : mpx)
		e.snd = i++;
	i = 0;
	for(auto &e : mpy)
		e.snd = i++;
	for(i = 0; i < n; i++) {
		ps[i].x = mpx[ps[i].x], ps[i].y = mpy[ps[i].y];
		mt[ps[i].x][ps[i].y]++;
	}
	for(i = 0; i < 3010; i++)
		for(j = 1; j < 3010; j++)
			mt[i][j] += mt[i][j-1];
	for(j = 0; j < 3010; j++)
		for(i = 1; i < 3010; i++)
			mt[i][j] += mt[i-1][j];
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d %d", &x, &y, &k);
		if(k > n) { puts("-1"); continue; }
		int l = 0, r = 1000000001;
		while(l < r) {
			int m = (l + r) / 2;
			if(get(x - m, y - m, x + m, y + m) >= k) r = m;
			else l = m + 1;
		}
		printf("%d\n", l);
	}
}

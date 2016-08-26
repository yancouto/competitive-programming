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

int pir(int n, int d) {
	int tot = 0;
	while(n > 0) {
		tot += n * n;
		n -= d;
	}
	return tot;
}

struct py {
	int n; char c;
	int tot;
};
py p[320]; int pn;
int dp[2][1000009];
int w[7][1000009];
int main() {
	int i, c, j, t = 0, k;
	for(i = 2; pir(i, 1) <= 1000000; i++)
		p[pn++] = {i, 'H', pir(i, 1)};
	for(i = 3; pir(i, 2) <= 1000000; i++)
		p[pn++] = {i, 'L', pir(i, 2)};
	sort(p, p + 320, [](py a, py b) { return a.tot < b.tot; });
	c = 1000000;
	for(i = 0; i <= 6; i++)
		for(j = 0; j <= c; j++)
			w[i][j] = 100000000;
	w[0][0] = 0;
	for(i = 0; i < 320; i++)
		for(j = c; j >= p[i].tot; j--)
			for(k = 6; k >= 1; k--) {
				if(w[k - 1][j - p[i].tot] != 100000000)
					w[k][j] = i;
			}
	while(scanf("%d", &c) != EOF && c) {
		for(i = 1; i <= 6 && w[i][c] == 100000000; i++);
		printf("Case %d:", ++t);
		if(i == 7) { puts(" impossible"); continue; }
		vector<py> v;
		while(c) {
			py &pi = p[w[i][c]];
			v.pb(pi);
			c -= pi.tot;
			i--;
		}
		sort(v.begin(), v.end(), [](py a, py b) { return a.tot > b.tot; });
		for(py pi : v)
			printf(" %d%c", pi.n, pi.c);
		putchar('\n');
	}
}

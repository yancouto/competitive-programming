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
const int MAX = 100009;
struct no {
	int i; pii p;
	bool operator < (no o) const { return p < o.p; }
	bool operator == (no o) const { return p == o.p; }
	no() {}
	no(int x, int y, int z) : p(x, y), i(z) {}
} l[MAX], g[2*MAX];
int c[2*MAX];
int p[MAX][19], r[MAX], lc[MAX], n, lg;
char s[MAX];
int lcp(int i, int j) {
	int t = 0;
	for(int k = lg - 1; k >= 0; k--)
		if(p[i + t][k] == p[j + t][k] && i + t + (1 << k) <= n && j + t + (1 << k) <= n)
			t += 1 << k;
	return t;
}
int d[256];
int main() {
	int i, j, k;
	while(true) {
		scanf("%s", s); n = strlen(s);
		if(s[0] == '*') return 0;
		for(i = 0; i < n; i++)
			p[i][0] = s[i];
		for(j = 1; ; j++) {
			for(i = 0; i < n; i++)
				l[i] = no(p[i][j-1], i + (1 << (j - 1)) < n? p[i + (1 << (j - 1))][j - 1] : -1, i);
			sort(l, l + n);
			for(i = 0; i < n; i++)
				p[l[i].i][j] = (i? p[l[i-1].i][j] + !(l[i] == l[i-1]) : 0);
			if(p[l[n-1].i][j] == n - 1) break;
		}
		lg = j + 1;
		for(i = 0; i < n; i++)
			r[p[i][lg - 1]] = i;
		lc[0] = 0;
		for(i = 0; i < n - 1; i++)
			lc[i] = lcp(r[i], r[i + 1]);
		int tot = lc[0], last = lc[0];
		for(i = 1; i < n - 1; i++)
			if(lc[i] > lc[i-1])
				tot += lc[i] - lc[i-1];
		printf("%d\n", tot);
	}
}

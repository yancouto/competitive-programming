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
const int MAX = 250002;
char s[MAX*2];
int p[MAX*2][2];
inline int& h(int i) { return p[i][0]; }
inline int& pot(int i) { return p[i][1]; }

bool eq(int i, int j, int sz) {
	int h1 = h(i + sz - 1) - mod(ll(h(i - 1)) * ll(pot(sz)));
	if(h1 < 0) h1 += modn;
	int h2 = h(j + sz - 1) - mod(ll(h(j - 1)) * ll(pot(sz)));
	if(h2 < 0) h2 += modn;
	return h1 == h2;
}

int n;
int lcp(int i, int j) {
	int l = 0, r = n;
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(eq(i, j, m)) l = m;
		else r = m - 1;
	}
	return l;
}

int c[MAX*2];
int l[MAX*2], g[MAX*2];
int j;
inline int g1(int i) { return p[i][!(j&1)]; }
inline int g2(int i) { return p[min(i+(1<<(j-1)), 2*n+1)][!(j&1)]; }
inline bool eq(int i, int j) {
	return pii(g1(i), g2(i)) == pii(g1(j), g2(j));
}

int main() {
	int i;
	scanf("%d %s", &n, s + 1);
	memmove(s + 1 + n, s + 1, n + 1);
	p[2*n+1][0] = p[2*n+1][1] = -1;
	for(i = 1; i <= 2*n; i++)
		l[i] = s[i];
	sort(l + 1, l + 2*n + 1);
	for(i = 1; i <= 2*n; i++)
		p[i][0] = lower_bound(l + 1, l + 2 * n + 1, s[i]) - l;
	for(j = 1; ; j++) {
		int sz = 0;
		for(i = 2*n; i > 0; i--) {
			if(g2(i) == -1) l[++sz] = i;
			else g[c[g2(i)]++ + g2(i)] = i;
		}
		for(i = 1; i <= 2*n; i++)
			while(c[i])
				l[++sz] = g[i + --c[i]];
		assert(sz == 2*n);
		sz = 0;
		for(i = 2*n; i > 0; i--)
			g[c[g1(l[i])]++ + g1(l[i])] = l[i];
		for(i = 1; i <= 2*n; i++)
			while(c[i])
				l[++sz] = g[i + --c[i]];
		assert(sz == 2*n);
		bool any = false;
		for(i = 1; i <= 2*n; i++)
			p[l[i]][j&1] = eq(l[i], l[i-1])? p[l[i-1]][j&1] : i, any |= eq(l[i], l[i-1]);
		if(!any) break;
	}
	for(i = 1; i <= 2*n; i++)
		c[p[i][j&1]] = i;
	j = 0;
	for(i = 1; i <= 2*n; i++)
		if(c[i] <= n)
			c[++j] = c[i];
	h(0) = 0; pot(0) = 1;
	for(i = 1; i <= 2 * n; i++) {
		h(i) = mod(ll(h(i - 1)) * 263ll + s[i]);
		pot(i) = mod(ll(pot(i - 1)) * 263ll);
	}
	double tot = 0;
	for(i = 1; i < n; i++)
		tot += lcp(c[i], c[i + 1]);
	printf("%.3f\n", tot / (n - 1));
}

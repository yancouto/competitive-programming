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
const int MAX = 601007;
struct no {
	pii p; int i;
	no() {}
	no(int a, int b, int c) : p(a, b), i(c) {}
	bool operator < (no o) const { return p < o.p; }
	bool operator == (no o) const { return p == o.p; }
} l[MAX];
int p[MAX][21], r[MAX], lc[MAX][21], n;
ll x[MAX][21];

int mn(int i, int j) {
	int e = 31 - __builtin_clz(j - i + 1);
	return min(lc[i][e], lc[j - (1 << e) + 1][e]);
}
ll qx(int i, int j) {
	int e = 31 - __builtin_clz(j - i + 1);
	return x[i][e] | x[j - (1 << e) + 1][e];
}

int lcp(int i, int j) {
	int t = 0;
	for(int k = 20; k >= 0; k--)
		if(p[i+t][k] == p[j+t][k] && i + t + (1 << k) <= n && j + t + (1 << k) <= n)
			t += 1 << k;
	return t;
}
char s[MAX];
int sz[MAX], ow[MAX], pos[MAX];
int main() {
	int i, j, f;
	while(scanf("%d", &f) != EOF && f) {
		n = 0;
		for(i = 0; i < f; i++) {
			scanf("%s", s + n);
			sz[i] = strlen(s + n);
			for(j = n; j < n + sz[i]; j++)
				ow[j] = i + 1;
			pos[i] = n;
			n += sz[i];
			ow[n] = 0;
			s[n++] = 'a' - 1 - i;
		}
		s[n] = '\0';
		for(i = 0; i < n; i++)
			p[i][0] = s[i];
		for(j = 1; j < 21; j++) {
			for(i = 0; i < n; i++)
				l[i] = no(p[i][j-1], i + (1 << (j - 1)) < n? p[i + (1 << (j - 1))][j - 1] : -1, i);
			sort(l, l + n);
			for(i = 0; i < n; i++)
				p[l[i].i][j] = i && l[i] == l[i-1]? p[l[i-1].i][j] : i;
		}
		for(i = 0; i < n; i++)
			r[p[i][20]] = i;
		for(i = 0; i < n - 1; i++)
			lc[i][0] = lcp(r[i], r[i+1]), x[i][0] = ((1ll << ow[r[i]]) | (1ll << ow[r[i+1]])) >> 1;
		for(j = 1; j < 20; j++)
			for(i = 0; i < n - 1; i++) {
				lc[i][j] = lc[i][j-1];
				x[i][j] = x[i][j-1];
				if(i + (1 << (j - 1)) < n - 1)
					lc[i][j] = min(lc[i][j], lc[i + (1 << (j - 1))][j - 1]),
					x[i][j] = x[i][j] | x[i + (1 << (j - 1))][j - 1];
			}
		set<ll> c;
		for(i = 0; i < f; i++) {
			int y = p[pos[i]][20];
			if(y < n - 1 && lc[y][0] >= sz[i]) continue;
			if(y && lc[y-1][0] >= sz[i]) continue;
			c.insert(1ll << i);
		}
		for(i = 0; i < n - 1; i++) {
			if(!lc[i][0]) continue;
			int le = 0, ri = i;
			while(le < ri) {
				int m = (le + ri) / 2;
				if(mn(m, i) == mn(i, i)) ri = m;
				else le = m + 1;
			}
			int ql = le;
			le = i; ri = n - 1;
			while(le < ri) {
				int m = (le + ri + 1) / 2;
				if(mn(i, m) == mn(i, i)) le = m;
				else ri = m - 1;
			}
			c.insert(qx(ql, ri));
		}
		c.erase(0ll);
		printf("%d\n", (int) c.size());
	}
}

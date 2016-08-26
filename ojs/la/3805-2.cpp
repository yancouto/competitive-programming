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
const int MAX = 600100;
struct no {
	pii p; int i;
	no() {}
	no(int a, int b, int c) : p(a, b), i(c) {}
	bool operator < (no o) const { return p < o.p; }
	bool operator == (no o) const { return p == o.p; }
} l[MAX];
int lc[MAX][21], p[MAX][21], r[MAX], K, n;
char s[MAX]; ll ow[MAX], lo[MAX][21];
int sz[MAX], st[MAX];
int lcp_(int i, int j) {
	int t = 0;
	for(int k = K - 1; k >= 0; k--)
		if(p[i+t][k] == p[j+t][k] && i + t + (1 << k) <= n && j + t + (1 << k) <= n)
			t += 1 << k;
	return t;
}
int lcp(int i, int j) {
	int e = 31 - __builtin_clz(j - i + 1);
	return min(lc[i][e], lc[j - (1 << e) + 1][e]);
}
ll ows(int i, int j) {
	int e = 31 - __builtin_clz(j - i + 1);
	return lo[i][e] | lo[j - (1 << e) + 1][e];
}

int main() {
	int i, j, f;
	while(scanf("%d", &f) != EOF && f) {
		n = 0;
		for(i = 0; i < f; i++) {
			scanf("%s", s + n);
			for(j = 0; s[j+n]; j++)
				ow[j+n] = (1ll << i);
			sz[i] = strlen(s + n);
			st[i] = n;
			n += sz[i];
			ow[n] = 0;
			s[n++] = 'z' + 1 + i;
		}
		s[n] = 0;
		for(i = 0; i < n; i++)
			p[i][0] = s[i];
		for(j = 0; j < 21; j++)
			p[n][j] = -1;
		for(j = 1; ; j++) {
			for(i = 0; i < n; i++)
				l[i] = no(p[i][j-1], p[min(i+(1<<(j-1)), n)][j-1], i);
			sort(l, l + n);
			bool any = false;
			for(i = 0; i < n; i++)
				p[l[i].i][j] = i && l[i] == l[i-1]? p[l[i-1].i][j] : i, any |= i && l[i] == l[i-1];
			if(!any) break;
		}
		K = j + 1;
		for(i = 0; i < n; i++)
			r[p[i][j]] = i;
		for(i = 0; i < n - 1; i++) {
			lc[i][0] = lcp_(r[i], r[i+1]);
			lo[i][0] = ow[r[i]] | ow[r[i+1]];
		}
		for(j = 1; j < 21; j++)
			for(i = 0; i < n - 1; i++) {
				lc[i][j] = lc[i][j-1];
				lo[i][j] = lo[i][j-1];
				if(i + (1 << (j - 1)) < n - 1)
					lc[i][j] = min(lc[i][j], lc[i+(1<<(j-1))][j-1]),
					lo[i][j] = lo[i][j] | lo[i+(1<<(j-1))][j-1];
			}
		set<ll> s;
		for(i = 0; i < f; i++) {
			int x = p[st[i]][K-1];
			if(x < n - 1 && lc[x][0] >= sz[i]) continue;
			if(x > 0 && lc[x - 1][0] >= sz[i]) continue;
			s.insert(1ll << i);
		}
		for(i = 0; i < n - 1; i++) {
			if(!lc[i][0]) continue;
			int l = 0, r = i;
			while(l < r) {
				int m = (l + r) / 2;
				if(lcp(m, i) == lcp(i, i)) r = m;
				else l = m + 1;
			}
			int ql = l;
			l = i; r = n - 1;
			while(l < r) {
				int m = (l + r + 1) / 2;
				if(lcp(i, m) == lcp(i, i)) l = m;
				else r = m - 1;
			}
			s.insert(ows(ql, r));
		}
		s.erase(0);
		printf("%d\n", s.size());
	}
}

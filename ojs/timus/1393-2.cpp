// WA??
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
const int MAX = 500010;
char s[MAX/2]; int n, *r;
int pot[MAX]; unsigned pot2[MAX];
int h[MAX]; unsigned h2[MAX];
int p[MAX][2];
inline int& pp(int i, int j) { return p[i][(j+2)&1]; }

bool eq(int a1, int b1, int a2, int b2) {
	bool a = mod(h[b1 + 1] - mod(ll(h[a1]) * pot[b1 - a1 + 1]) + modn) == mod(h[b2 + 1] - mod(ll(h[a2]) * pot[b2 - a2 + 1]) + modn);
	bool b = h2[b1 + 1] - h2[a1] * pot2[b1 - a1 + 1] == h2[b2 + 1] - h2[a2] * pot2[b2 - a2 + 1];
	return a && b;
}

int lcp(int i, int j) {
	if(s[i] != s[j]) return 0;
	int l = 1, r = min(n - i, n - j);
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(eq(i, i + m - 1, j, j + m - 1)) l = m;
		else r = m - 1;
	}
	return l;
}
int c[MAX];

struct no {
	pii p; int i;
	no(int a, int b, int c) : p(a, b), i(c) {}
	no() {}
	bool operator < (no o) const { return p < o.p; }
	bool operator == (no o) { return p == o.p; }
} l[MAX], g[MAX];
int d[256];
int main() {
	int i, j, k;
	scanf("%d %s", &n, s);
	n <<= 1;
	pot[0] = 1; pot2[0] = 1;
	for(i = 0; i < n; i++) {
		pot[i + 1] = mod(43ll * pot[i]);
		h[i + 1] = mod(43ll * h[i] + s[i%(n/2)] - 'A' + 1);
		pot2[i + 1] = 33u * pot2[i];
		h2[i + 1] = 33u * h2[i] + s[i%(n/2)] - 'A' + 1;
	}
	for(i = 0; i < n; i++)
		d[s[i]]++;
	for(i = 1; i < 256; i++)
		d[i] += d[i-1];
	for(j = 0; ; j++) {
		int sz = 0;
		for(i = 0; i < n; i++) {
			if(j) l[i] = no(pp(i, j - 1), i + (1 << (j - 1)) < n? pp(i + (1 << (j - 1)), j - 1) : -1, i);
			else l[i] = no(d[s[i] - 1], -1, i);
			if(l[i].p.snd == -1) l[sz++] = l[i];
			else g[l[i].p.snd + c[l[i].p.snd]++] = l[i];
		}
		for(i = 0; i < n; i++) {
			for(k = 0; k < c[i]; k++)
				l[sz++] = g[i + k];
			c[i] = 0;
		}
		assert(sz == n);
		for(i = 0; i < n; i++)
			g[l[i].p.fst + c[l[i].p.fst]++] = l[i];
		sz = 0;
		for(i = 0; i < n; i++) {
			for(k = 0; k < c[i]; k++)
				l[sz++] = g[i + k];
			c[i] = 0;
		}
		assert(sz == n);

		bool any = false;
		for(i = 0; i < n; i++)
			pp(l[i].i, j) = i && l[i] == l[i - 1]? pp(l[i - 1].i, j) : i, any |= i && l[i] == l[i-1];
		if(!any) break;
	}
	for(i = 0; i < n; i++)
		c[pp(i, j)] = i;
	i = 0; ll tot = 0;
	while(c[i] >= n/2) i++;
	for(j = i; ; i = j) {
		j++;
		while(j < n && c[j] >= n/2) j++;
		if(j == n) break;
		tot += min(lcp(c[i], c[j]), n/2);
	}
	printf("%.3f\n", double(tot) / (n / 2 - 1.));
}

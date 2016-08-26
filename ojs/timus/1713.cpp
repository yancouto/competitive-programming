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
const int MAX = 101009;
struct no {
	pii p; int i;
	no() {}
	no(int a, int b, int c) : p(a, b), i(c) {}
	bool operator < (no o) const { return p < o.p; }
} l[MAX];
char s2[1009]; int s[MAX], r[MAX], ow[MAX], mx[1009][102], p[MAX][18], pos[1009], sz[1009];
int lc[MAX][18];
int n, g;
int lcp_(int i, int j) {
	int t = 0;
	for(int k = g; k >= 0; k--)
		if(p[i+t][k] == p[j+t][k] && i + t + (1 << k) <= n && j + t + (1 << k) <= n)
			t += 1 << k;
	return t;
}

int lcp(int i, int j) {
	int e = 31 - __builtin_clz(j - i + 1);
	int v = min(lc[i][e], lc[j - (1 << e) + 1][e]);
	return v;
}


int main() {
	int i, m, j;
	scanf("%d", &m);
	n = 0;
	for(i = 0; i < m; i++) {
		scanf("%s", s2);
		int k = strlen(s2);
		pos[i] = n; sz[i] = k;
		for(j = 0; j < k; j++)
			ow[n + j] = i, s[n + j] = s2[j], mx[i][j] = 1;
		n += k;
		ow[n] = -1;
		s[n++] = 257 + i; // separador
	}
	for(i = 0; i < n; i++)
		p[i][0] = s[i];
	for(j = 0; j < 18; j++)
		p[n][j] = -1;
	for(j = 1; ; j++) {
		for(i = 0; i < n; i++)
			l[i] = no(p[i][j - 1], p[min(i + (1 << (j - 1)), n)][j - 1], i);
		sort(l, l + n);
		p[l[0].i][j] = 0;
		for(i = 1; i < n; i++)
			p[l[i].i][j] = p[l[i-1].i][j] + (l[i].p != l[i-1].p);
		if(p[l[n-1].i][j] == n - 1) break;
	}
	g = j;
	for(i = 0; i < n; i++)
		r[p[i][g]] = i;
	for(i = 0; i < n - 1; i++)
		lc[i][0] = lcp_(r[i], r[i+1]);
	for(j = 1; j < 18; j++)
		for(i = 0; i < n - 1; i++) {
			lc[i][j] = lc[i][j-1];
			if(i + (1 << (j - 1)) < n - 1)
				lc[i][j] = min(lc[i][j], lc[i + (1 << (j - 1))][j - 1]);
		}
	int le = -1, ri = -1;
	for(i = 0; i < n; i++) {
		if(ri < i) {
			le = ri = i;
			while(ri < n && ow[r[ri]] == ow[r[le]]) ri++;
			ri--;
		}
		if(ow[r[i]] == -1) continue;
		int &a = mx[ow[r[i]]][r[i] - pos[ow[r[i]]]];
		if(ri < n - 1) a = max(a, lcp(i, ri) + 1);
		if(le > 0) a = max(a, lcp(le - 1, i - 1) + 1);
	}
	for(i = 0; i < m; i++) {
		int xi = 0;
		for(j = 1; j < sz[i]; j++)
			if(j + mx[i][j] <= sz[i] && mx[i][j] < mx[i][xi]) {
				xi = j;
			}
		for(j = 0; j < mx[i][xi]; j++)
			putchar(s[pos[i] + xi + j]);
		putchar('\n');
	}
}

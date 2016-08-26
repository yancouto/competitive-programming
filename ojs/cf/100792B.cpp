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
const int N = 500009;
char s[N], p[N], p2[N];
int f[N], f2[N], le[N], ri[N];
int tr[N << 2];
inline int L(int i) { return i << 1; }
inline int R(int i) { return L(i) + 1; }

void kmp(char *s, int *f) {
	for(int i = 1; s[i]; i++) {
		f[i] = f[i - 1];
		while(f[i] && s[f[i]] != s[i])
			f[i] = f[f[i]];
		if(s[f[i]] == s[i]) f[i]++;
	}
}

int rmq[N][20];
void build(int n) {
	for(int i = n - 1; i >= 0; i--) {
		rmq[i][0] = le[i];
		for(int j = 1; j < 20; j++)
			rmq[i][j] = max(rmq[i][j - 1], rmq[min(n, i + (1 << (j - 1)))][j - 1]);
	}
}

inline int query(int l, int r) {
	int e = 31 - __builtin_clz(r - l + 1);
	return max(rmq[l][e], rmq[r - (1 << e) + 1][e]);
}

int main() {
	scanf("%s %s", s, p);
	int n = strlen(s), i;
	memcpy(s + n, s, n);
	n <<= 1;
	kmp(p, f);
	int pn = strlen(p);
	memcpy(p2, p, pn);
	reverse(p2, p2 + pn);
	kmp(p2, f2);
	int c = 0;
	for(i = 0; i < n; i++) {
		while(s[i] != p[c] && c)
			c = f[c];
		if(s[i] == p[c]) c++;
		ri[i - c + 1] = c;
		if(c == pn) { printf("%d\n", n / 2); return 0; }
	}
	c = 0;
	for(i = n - 1; i >= 0; i--) {
		while(s[i] != p2[c] && c)
			c = f2[c];
		if(s[i] == p2[c]) c++;
		le[i + c - 1] = c;
	}
	build(n);

	int best = -1;
	for(i = 1; i < n; i++) {
		int L = max(0, i + ri[i] - n/2 + (pn - ri[i])), r = i - 1;
		int l = L;
		if(query(l, r) < pn - ri[i]) continue;
		while(l < r) {
			int m = (l + r) / 2;
			if(query(L, m) >= pn - ri[i]) r = m;
			else l = m + 1;
		}
		best = max(best, pn + (i - l - 1));
	}
	printf("%d\n", best);
}

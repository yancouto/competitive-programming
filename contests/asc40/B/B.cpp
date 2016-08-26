#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 912345;
int v[N], pos[N];

int cn, cd, ns, en;
char s[N];
struct edge {
	int a, b;
	int v;
	inline int len() { return b - a + 1; }
	inline char operator[](int i) { return s[a + i - 1]; }
};

int suf[N];
map<char, edge> tr[N];
const int null = 0;

edge ce;
int n;

void sufftree() {
	s[++n] = '$';
	en = 1;
	ns = cn = cd = 0;
	int i = 1, j;
	for(j = 1; j <= n; j++)
		for(; i <= j; i++) {
			if(ns != null && cd == 0) {
				suf[ns] = cn;
				ns = null;
			}
			if(cd? ce[cd + 1] == s[j] : tr[cn].count(s[j])) {
				if(cd++ == 0) ce = tr[cn][s[j]];
				if(cd == ce.len()) {
					cd = 0;
					cn = ce.v;
				}
				break;
			} else if(cd > 0) {
				if(ns) suf[ns] = en;
				tr[en][ce[cd + 1]] = {ce.a + cd, ce.b, ce.v};
				tr[en][s[j]] = {j, n, en + 1};
				tr[cn][ce[1]] = {ce.a, ce.a + cd - 1, en};
				ns = en;
				en += 2;
				int g = cn? j - cd : i + 1;
				if(cn > 0) cn = suf[cn];
				while(g < j && g + tr[cn][s[g]].len() <= j) {
					ce = tr[cn][s[g]];
					cn = ce.v;
					g += ce.len();
				}
				cd = j - g;
				if(cd > 0) ce = tr[cn][s[g]];
			} else {
				tr[cn][s[j]] = {j, n, en++};
				cn = suf[cn];
			}
		}
}

int sn = 0;
int K[312345], a[312345];
void dfs(int u, int sz) {
	for(auto e : tr[u])
		if(u || e.fst != '$')
			dfs(e.snd.v, sz + e.snd.len());
	if(tr[u].empty()) K[sn++] = n - sz;
}

int main() {
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(...) fprintf(stderr, ...)
	freopen("binary.in", "r", stdin);
	freopen("binary.out", "w", stdout);
#else
#	define LLD "%lld"
#	define debug(...) {}
#endif
	int i, j, x;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]); a[i]--;
		pos[a[i]] = i;
	}
	for(i = 0; i < n && pos[n - 1 - i] == i; i++);
	j = i;
	for(; i < n; i++) {
		if(pos[n - 1 - i] >= pos[n - 1 - j])
			v[n - 1 - i] = 1;
	}
	for(i = 1; i <= n; i++)
		s[i] = '0' + v[i - 1];
	sufftree();
	dfs(0, 0);
	n--;
	for(i = 0; i < n && K[i] == a[i]; i++);
	if(i < n) { puts("Error"); return 0; }
	for(i = 0; i < n; i++)
		putchar('0' + v[i]);
	putchar('\n');
}

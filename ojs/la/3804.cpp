#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 112345;
int seen[N];
int c[2 * N], cn;
int bad; ll badval;
int bip[N], co[N], cp[N];
vector<pii> adj[N];

int st[N], sn;
void dfs(int cn, int u, int c) {
	if(seen[u]) {
		if(c == co[u]) return;
		if(!bip[cn]) return;
		bip[cn] = 0;
		int i;
		st[sn++] = u;
		for(i = 0; st[i] != u; i++);
		ll tot = 0;
		ll cur = 1;
		for(; i < sn - 1; i++)
			for(pii e : adj[st[i]])
				if(e.fst == st[i + 1]) {
					tot += e.snd * cur;
					cur = -cur;
					break;
				}
		bad = u;
		assert(!(tot % 2));
		badval = tot / 2;
		return;
	}
	cp[u] = cn;
	st[sn++] = u;
	seen[u] = 1;
	co[u] = c;
	for(pii e : adj[u])
		dfs(cn, e.fst, !c);
	sn--;
}

ll val[N];
void go(int u, ll v) {
	//printf("go(%d, %lld)\n", c[u], v);
	if(seen[u] == 2) return assert(v == val[u]);
	val[u] = v;
	seen[u] = 2;
	for(pii e : adj[u]) {
		//printf("%d->%d (%lld)\n", c[u], c[e.fst], e.snd);
		go(e.fst, e.snd - v);
	}
}

int a[N], b[N], w[N];
int main() {
	int i, m, q;
	while(scanf("%d %d", &m, &q) != EOF && (m || q)) {
		cn = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a[i], &b[i], &w[i]);
			c[cn++] = a[i];
			c[cn++] = b[i];
			if(a[i] == b[i]) w[i] *= 2;
		}
		sort(c, c + cn);
		cn = unique(c, c + cn) - c;
		for(i = 0; i < cn; i++) adj[i].clear(), seen[i] = 0;
		for(i = 0; i < m; i++) {
			a[i] = lower_bound(c, c + cn, a[i]) - c;
			b[i] = lower_bound(c, c + cn, b[i]) - c;
			//printf("%d <-> %d\n", a[i], b[i]);
			adj[a[i]].pb(pii(b[i], w[i]));
			adj[b[i]].pb(pii(a[i], w[i]));
		}
		for(i = 0; i < cn; i++) {
			if(seen[i]) continue;
			sn = 0;
			bip[i] = 1;
			dfs(i, i, 0);
			if(bip[i]) bad = i, badval = 0;
			//puts("======");
			go(bad, badval);
		}
		for(i = 0; i < q; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			if(!binary_search(c, c + cn, a) || !binary_search(c, c + cn, b)) { puts("*"); continue; }
			a = lower_bound(c, c + cn, a) - c;
			b = lower_bound(c, c + cn, b) - c;
			if(cp[a] == cp[b] && bip[cp[a]] && co[a] != co[b]) { printf("%lld\n", val[a] + val[b]); continue; }
			if(bip[cp[a]] || bip[cp[b]]) { puts("*"); continue; }
			printf("%lld\n", (a == b? val[a] : val[a] + val[b]));
		}
		puts("-");
	}
}

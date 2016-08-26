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
int p2[109], ppa, ppb, k, n;
int pai[109], d[109], seen[109];
vector<pii> adj[109];
void solve(int a) {
	int i;
	for(i = 0; i < n; i++)
		d[i] = 1000000, seen[i] = 0;
	d[a] = 0; pai[a] = a;
	while(true) {
		int x = -1;
		for(i = 0; i < n; i++)
			if(!seen[i] && (x == -1 || d[i] < d[x]))
				x = i;
		if(x == -1) return;
		seen[x] = 1;
		for(pii e : adj[x]) {
			if(d[x] + e.snd < d[e.fst]) {
				d[e.fst] = d[x] + e.snd;
				pai[e.fst] = x;
			}
			if(seen[e.fst] && pai[x] != e.fst && k > d[x] + d[e.fst] + e.snd) {
				k = d[x] + d[e.fst] + e.snd;
				ppa = x; ppb = e.fst;
				memcpy(p2, pai, sizeof pai);
			}
		}
	}
}

int main() {
	int i, m, a, b, c;
	while(scanf("%d %d", &n, &m) != EOF) {
		if(n == -1) return 0;
		for(i = 0; i < n; i++)
			adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			adj[--a].pb(pii(--b, c));
			adj[b].pb(pii(a, c));
		}
		k = 1000000;
		for(i = 0; i < n; i++)
			solve(i);
		if(k >= 100000) { puts("No solution."); continue; }
		int a = ppa;
		int st[109], sn = 0;
		while(p2[a] != a) {
			printf("%d ", a + 1);
			a = p2[a];
		}
		a = ppb;
		while(p2[a] != a) {
			st[sn++] = a;
			a = p2[a];
		}
		printf("%d", a + 1);
		while(sn) printf(" %d", st[--sn] + 1);
		putchar('\n');
	}
}

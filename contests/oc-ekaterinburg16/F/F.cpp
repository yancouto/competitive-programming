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

const int N = 1123;
int ord[N], on, n;
int st[N], sn, low[N], d[N], tempo, cm[N];
bool seen[N];
vector<int> adj[N], cmp[N];

void dfs(int u) {
	seen[u] = true;
	st[sn++] = u;
	low[u] = d[u] = tempo++;
	for(int v : adj[u])
		if(seen[v]) {
			low[u] = min(low[u], d[v]);
		} else {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
	if(low[u] == d[u]) {
		int a;
		do {
			a = st[--sn];
			d[a] = INT_MAX;
			cm[a] = u;
			cmp[u].pb(a);
			//printf("%d in comp of %d\n", a+1, u+1);
		} while(a != u);
		ord[on++] = u;
	}
}

int S[N], sz[N];
vector<int> g[N], ans[N], rev[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
	for(int v : g[b]) g[a].pb(v);
}

int at[N], an;

int main() {
	int a, b, m, i, j, k, s;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1, g[i].pb(i);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		rev[b].pb(a);
		join(a, b);
	}
	for(i = 0; i < n; i++)
		if(find(i) == i) {
			on = 0;
			for(int a : g[i])
				if(!seen[a])
					dfs(a);
			reverse(ord, ord + on);
			for(j = 0; j < on; j++) {
				a = ord[j]; s = cmp[a].size();
				//printf("cmp of %d (%d)\n", a+1, s);
				if(s > 1)
					for(k = 0; k < s; k++) {
						ans[cmp[a][k]].pb(cmp[a][(k + 1) % s]);
						//printf("%d->%d\n", cmp[a][k]+1, cmp[a][(k+1)%s]+1);
					}
				an++;
				for(k = j + 1; k < on; k++) {
					for(int v : cmp[ord[k]]) {
						for(int u : rev[v])
							if(cm[u] != a && at[cm[u]] == an)
								at[cm[v]] = an;
					}
					for(int v : cmp[ord[k]]) {
						for(int u : rev[v])
							if(at[cm[v]] != an && cm[u] == a) {
								at[cm[v]] = an;
								//printf("|%d->%d\n", a+1, cm[v]+1);
								ans[a].pb(cm[v]);
							}
					}
				}
			}
		}
	int ct = 0;
	for(i = 0; i < n; i++) ct += ans[i].size();
	printf("%d %d\n", n, ct);
	for(i = 0; i < n; i++)
		for(int v : ans[i])
			printf("%d %d\n", i+1, v+1);
}

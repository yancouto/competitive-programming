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
vector<int> cit[502];
vector<pii> adj[502];
int t;

int S[502], sz[502];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}
set<int> s[502];
int seen[502], d[502], low[502], tempo;
void dfs(int u, int p) {
	if(seen[u]) return;
	seen[u] = true;
	d[u] = low[u] = tempo++;
	for(pii e : adj[u])
		if(e.fst != p) {
			dfs(e.fst, u);
			low[u] = min(low[u], low[e.fst]);
			if(low[e.fst] > d[u]) {
				s[e.fst].erase(e.snd);
				s[u].erase(e.snd);
			}
		} else p = -1;
}
int n;
int mn(int v) {
	if(!s[v].empty()) return *s[v].begin();
	for(int i = 0; i < n; i++)
		if(v == cit[i].front() || v == cit[i].back())
			return i;
}

int main() {
	int c, i, k, j, x;
	while(true) {
		t++;
		scanf("%d %d", &n, &c);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			cit[i].clear();
		int rc = c;
		for(i = 0; i < c; i++) {
			scanf("%d", &k);
			S[i] = i; sz[i] = 1;
			adj[i].clear();
			if(!k) rc--;
			for(j = 0; j < k; j++) {
				scanf("%d", &x);
				cit[x].pb(i);
			}
		}
		for(i = 0; i < n; i++)  {
			join(cit[i].front(), cit[i].back());
			adj[cit[i].front()].pb(pii(cit[i].back(), i));
			adj[cit[i].back()].pb(pii(cit[i].front(), i));
		}
		int odd = 0;
		for(i = 0; i < c; i++)
			odd += adj[i].size() & 1;
		if((odd != 0 && odd != 2) || sz[find(cit[0].back())] != rc) {
			puts("-1");
			continue;
		}
		if(odd == 0) {
			puts("0");
			continue;
		}
		for(i = 0; i < c; i++) {
			s[i].clear();
			for(pii v : adj[i])
				s[i].insert(v.snd);
		}
		tempo = 0;
		memset(seen, 0, sizeof seen);
		dfs(cit[0].back(), -1);
		for(i = 0; i < c; i++)
			if(adj[i].size() & 1)
				break;
		int ma = mn(i);
		for(i++; i < c; i++)
			if(adj[i].size() & 1)
				break;
		printf("%d\n", min(ma, mn(i)));
	}
}

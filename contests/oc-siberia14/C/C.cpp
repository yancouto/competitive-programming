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

string back[10009];
map<string, int> mp;
inline int get(string s) {
	if(!mp.count(s))
		back[mp[s] = mp.size() - 1] = s;
	return mp[s];
}
int w;

vector<int> adj[10009];
int tam[10009], som[10009];

int dfs(int u) {
	tam[u] = 1;
	for(int v : adj[u])
		tam[u] += dfs(v);
	for(int i = adj[u].size() - 2; i >= 0; i--)
		som[adj[u][i]] += som[adj[u][i + 1]];
	return som[u] = tam[u];
}

short memo[10002][10004];
int solve(int u, int m, int k) {
	if(m == adj[u].size()) return 0; // ou 1?
	int v = adj[u][m];
	short &r = memo[v][k];
	if(r != -1) return r;
	r = 12000;
	if(k > 1) r = solve(u, m, k - 1);
	if(m == 0) r = min<short>(r, 1 + solve(u, 0, w - 1));
	for(int l = max(k - som[v] + tam[v], 1); l <= k && l <= tam[v]; l++)
		r = min<short>(r, solve(v, 0, l - 1) + solve(u, m + 1, k - l));
	//printf("%d -> %d, %d (%d)\n", u, v, k, int(r));
	return r;
}

vector<pii> con[10009];
int close[10009];

void build(int u, int m, int k, int dep, int p) {
	if(m == adj[u].size()) return;
	int v = adj[u][m];
	short &r = memo[v][k];
	if(k > 1 && r == solve(u, m, k - 1)) return build(u, m, k - 1, dep, p);
	if(m == 0 && r == 1 + solve(u, 0, w - 1)) {
		con[u].pb(pii(u, 0)); close[u] = 1;
		return build(u, 0, w - 1, 0, u);
	}
	for(int l = max(k - som[v] + tam[v], 1); l <= k && l <= tam[v]; l++)
		if(r == solve(v, 0, l - 1) + solve(u, m + 1, k - l)) {
			con[p].pb(pii(v, dep + 1));
			build(v, 0, l - 1, dep + 1, p);
			build(u, m + 1, k - l, dep, p);
			return;
		}
}

int st[10009], sn = 0;
int dir[10009];
char ln[1000009];
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	fgets(ln, sizeof ln, stdin);
	sscanf(ln, "%d", &w);
	while(true) {
		fgets(ln, sizeof ln, stdin);
		if(feof(stdin)) break;
		int i = 0;
		while(ln[2*i] == '|') i++;
		int g = get(ln + 2 * i + 1);
		dir[g] = (ln[2*i] == '-');
		st[i] = g;
		if(i > 0) adj[st[i-1]].pb(g);
	}
	memset(memo, -1, sizeof memo);
	dfs(0);
	int s = 1 + solve(0, 0, w - 1);
	if(s > 10010) { puts("IMPOSSIBLE"); return 0; }
	else printf("%d\n", s);
	con[0].pb(pii(0, 0));
	build(0, 0, w - 1, 0, 0);
	for(int i = 0; i < mp.size(); i++) {
		if(con[i].empty()) continue;
		for(pii p : con[i]) {
			for(int j = 0; j < p.snd; j++)
				printf("| ");
			char c = ".-"[dir[p.fst]];
			if(close[p.fst] && p.fst != i) c = '+';
			printf("%c%s", c, back[p.fst].c_str());
		}
		puts("====================");
	}
}

// WA ideia errada mas talvez de pra adaptar
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
const int N = 300009;
int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
vector<int> adj[N];
void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(adj[a].size() < adj[b].size()) swap(a, b);
	adj[a].insert(adj[a].end(), adj[b].begin(), adj[b].end());
	S[b] = a;
}
char s[N];
int df[N];
int c[N];
bool cmp(int u, int v) { return s[u] < s[v]; }

int dfs0(int u, int p) {
	if(p != -1) {
		int i;
		for(i = 0; adj[u][i] != p; i++);
		adj[u].erase(adj[u].begin() + i);
	}
	for(int v : adj[u])
		dfs0(v, u);
}

int dfs(int u) {
	sort(adj[u].begin(), adj[u].end(), cmp);
	int &d = df[u]; d = 1;
	for(int i = 0; i < adj[u].size();) {
		int j = i + 1;
		while(j < adj[u].size() && s[adj[u][i]] == s[adj[u][j]])
			join(adj[u][i], adj[u][j++]);
		d += dfs(find(adj[u][i]));
		i = j;
	}
	return d;
}


int main() {
	int i, a, b, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &c[i]), S[i] = i, sz[i] = 1;
	scanf("%s", s);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs0(0, -1);
	dfs(0);
	int mx = -1;
	for(i = 0; i < n; i++)
		mx = max(mx, c[i] + df[find(i)]);
	printf("%d\n", mx);
	int ct = 0;
	for(i = 0; i < n; i++)
		if(mx == c[i] + df[find(i)])
			ct++;
	printf("%d\n", ct);
}

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

string ans[3] = {"CW", "CCW", "-"};

int v[112345];
vector<int> adj[112345];
void dfs(int u, int p, int val) {
	v[u] = val;
	for(int v : adj[u])
		if(v != p)
			dfs(v, u, !val);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int i, n, k, m, x;
	scanf("%d %d", &n, &k); k--;
	for(i = 0; i < n; i++) {
		v[i] = 2;
		scanf("%d", &m);
		while(m--) {
			scanf("%d", &x); x--;
			adj[i].pb(x);
		}
	}
	dfs(k, k, 0);
	for(i = 0; i < n; i++)
		if(adj[i].size() <= 1)
			printf("%s\n", ans[v[i]].c_str());
}

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

vector<int> ans;

const int N = 112345;
vector<int> pt[N], adj[N];
set<int> S[N];

bool add(int i, int u) {
	if(S[u].count(i)) return true;
	//printf("[%d].insert(%d)\n", u, i);
	S[u].insert(i);
	return false;
}

void go(int u, int p) {
	bool bad = false;
	//puts("init");
	for(int p : pt[u])
		bad = add(p, u) || bad;
	//puts("---");
	for(int v : adj[u]) {
		if(v == p) continue;
		go(v, u);
		if(S[v].size() > S[u].size())S[u].swap(S[v]);
		//printf("%d add %d\n", u, v);
		for(int p : S[v])
			bad = add(p, u) || bad;
		//puts("---");
	}
	if(bad) {
		ans.pb(u);
		S[u].clear();
	}
}

int main() {
	int i, n, m;
	scanf("%d", &n);
	int a, b;
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	scanf("%d", &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		pt[a].pb(i);
		pt[b].pb(i);
	}
	go(0, 0);
	printf("%d\n", int(ans.size()));
	for(int u : ans)
		printf("%d ", u + 1);
	putchar('\n');
}

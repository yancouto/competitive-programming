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
int ok[N];

bool add(set<int> &s, int i) {
	if(ok[i]) return false;
	if(s.count(i)) {
		return true;
	} else {
		s.insert(i);
		return false;
	}
}

vector<int> adj[N], mrk[N];
set<int> S[N];
int tot = 0;

void go(int u, int p) {
	bool any = false;
	for(int v : adj[u]) {
		if(v == p) continue;
		go(v, u);
		if(S[v].size() > S[u].size()) S[u].swap(S[v]);
		for(int x : S[v]) any = add(S[u], x) || any;
	}
	for(int x : mrk[u]) any = add(S[u], x) || any;
	if(any) {
		tot++;
		for(int x : S[u]) ok[x] = 1;
		S[u].clear();
	}
}

int main() {
	int i, n, m, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b); adj[b].pb(a);
	}
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		mrk[a].pb(i);
		mrk[b].pb(i);
	}
	go(0, -1);
	printf("%d\n", tot);
}

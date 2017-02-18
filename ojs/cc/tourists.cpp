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

void imp() {
	puts("NO");
	exit(0);
}

const int N = 212345;
vector<pii> adj[N];
int ea[N], eb[N], us[N];

void go(int u) {
	while(true) {
		while(!adj[u].empty() && us[adj[u].back().snd]) adj[u].pop_back();
		if(adj[u].empty()) return;
		pii e = adj[u].back(); adj[u].pop_back();
		us[e.snd] = 1;
		go(e.fst);
		ea[e.snd] = u; eb[e.snd] = e.fst;
	}
}

int main() {
	int i, n, m, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(pii(b, i));
		adj[b].pb(pii(a, i));
	}
	for(i = 0; i < n; i++) if(adj[i].size() & 1) imp();
	if(n > 1) for(i = 0; i < n; i++) if(adj[i].empty()) imp();
	go(0);
	for(int u = 0; u < n; u++) while(!adj[u].empty() && us[adj[u].back().snd]) adj[u].pop_back();
	for(i = 0; i < n; i++) if(!adj[i].empty()) imp();
	puts("YES");
	for(i = 0; i < m; i++)
		printf("%d %d\n", ea[i] + 1, eb[i] + 1);
}

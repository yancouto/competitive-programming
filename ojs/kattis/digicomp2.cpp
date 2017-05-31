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

const int N = 1123456;
int seen[N], st[N];
vector<int> adj[N];
ll balls[N];
deque<int> top;

void dfs(int u) {
	if(seen[u]) return;
	seen[u] = true;
	for(int v : adj[u])
		dfs(v);
	top.push_front(u);
}

int main() {
	ll n; int m, i, l, r; char c;
	scanf("%lld %d", &n, &m);
	for(i = 1; i <= m; i++) {
		scanf(" %c %d %d", &c, &l, &r);
		st[i] = (c == 'R');
		adj[i].pb(l);
		adj[i].pb(r);
	}
	for(i = 0; i <= m; i++)
		if(!seen[i])
			dfs(i);
	balls[1] = n;
	for(int u : top) {
		if(u == 0) continue;
		for(int v : adj[u]) balls[v] += balls[u] / 2;
		if(balls[u] & 1) {
			balls[adj[u][st[u]]]++;
			st[u] = !st[u];
		}
	}
	assert(balls[0] == n);
	for(i = 1; i <= m; i++)
		putchar(st[i]? 'R' : 'L');
	putchar('\n');
}

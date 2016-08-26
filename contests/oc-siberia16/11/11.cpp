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

const int N = 112345;

vector<int> adj[N];
int g[N], tot;

void go(int a) {
	if(g[a]) return;
	g[a] = 1; tot++;
	for(int b : adj[a])
		go(b);
	adj[a].clear();
}

int main() {
	int i, n, k, m, x, a, b;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &n, &k, &m);
	for(i = 0; i < k; i++) {
		scanf("%d", &x); x--;
		g[x] = 1;
		tot++;
	}
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		if(g[b] && !g[a]) go(a);
		else if(!g[a]) adj[b].pb(a);
		printf("%d\n", tot);
	}
}

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
const int N = 112;
vector<int> adj[N], best, sel;
int block[N], mx, p[N], n;

void go(int i, int cur) {
	if(cur > mx) {
		best = sel;
		mx = cur;
	}
	if(i == n || n - i + cur <= mx) return;
	int u = p[i];
	if(!block[u]) {
		for(int v : adj[u]) block[v]++;
		sel.pb(u);
		go(i + 1, cur + 1);
		sel.pop_back();
		for(int v : adj[u]) block[v]--;
	}
	go(i + 1, cur);
}

int main() {
	int i, m, a, b;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) p[i] = i, adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		sort(p, p + n, [](int i, int j) { return adj[i].size() < adj[j].size(); });
		mx = 0; go(0, 0);
		printf("%d\n%d", mx, best[0] + 1);
		for(i = 1; i < best.size(); i++) printf(" %d", best[i] + 1);
		printf("\n");
	}
}

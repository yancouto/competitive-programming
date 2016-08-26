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
const int MAX = 50009;
int x[MAX], y[MAX], w[2], seen[MAX];
vector<int> adj[MAX];
void dfs(int u, int c) {
	if(seen[u]) return;
	seen[u] = true;
	w[c]++;
	for(int v : adj[u])
		dfs(v, !c);
}

map<int, int> ln[500109];
ll dist(int i, int j) {
	return ll(x[i] - x[j]) * ll(x[i] - x[j]) + ll(y[i] - y[j]) * ll(y[i] - y[j]);
}

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]); y[i] += 10;
		ln[y[i]][x[i]] = i;
	}
	for(i = 0; i < n; i++) {
		for(j = y[i] - 5; j <= y[i] + 5; j++) {
			auto it = ln[j].lower_bound(x[i] - 5);
			auto it2 = ln[j].upper_bound(x[i] + 5);
			for(; it != it2; ++it) {
				if(dist(i, it->snd) <= 25)
					adj[i].pb(it->snd);
			}
		}
	}
	int tot = 0;
	for(i = 0; i < n; i++) {
		w[0] = 0; w[1] = 0;
		dfs(i, 0);
		tot += min(w[0], w[1]);
	}
	printf("%d\n", tot);
}

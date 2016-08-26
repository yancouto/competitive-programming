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

int a, b, c;
vector<int> adj[102];
int n, m;
int memo[60][102][60];
int solve(int i, int mv, int turn) {
	int &r = memo[i][mv][turn];
	if(r != -1) return r;
	if(mv == 0) {
		if(i == n - 1) return r = 0;
		if(turn == n) return r = 1e5;
		r = max(solve(i, a, turn + 1), solve(i, b, turn + 1));
		r = max(r, solve(i, c, turn + 1));
		return r = r + 1;
	}
	r = 1e5;
	for(int j : adj[i])
		r = min(r, solve(j, mv - 1, turn));
	return r;
}

int main() {
	int i, x, y;
	while(scanf("%d %d %d %d %d", &n, &m, &a, &b, &c) != EOF) {
		for(i = 0; i < n; i++) adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			adj[x-1].pb(y-1);
		}
		memset(memo, -1, sizeof memo);
		int ans = solve(0, 0, 0);
		if(ans > n) puts("IMPOSSIBLE");
		else printf("%d\n", ans);
	}
}

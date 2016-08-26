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

struct ed {
	int v, t, m;
};

int p[6][103];

vector<ed> adj[105];

struct no {
	int i, t, b, k;
};

deque<no> q;
int N, M, B, K, R, T;
int seen[102][202][6][6];
void dfs(no x) {
	if(seen[x.i][x.t][x.b][x.k]) return;
	seen[x.i][x.t][x.b][x.k] = 1;
	if(!x.t) return;
	if((x.i == 0 || x.i == N - 1) && x.k) return;
	if(x.i == N - 1) return;
	dfs(no{x.i, x.t - 1, x.b, x.k});
	dfs(no{x.i, x.t - 1, x.b, (x.k + 1) % K});
	if(x.b && x.i && x.i != N - 1) dfs(no{x.i, x.t - 1, x.b - 1, (x.k + 1) % K});
	if(x.b != B && x.i && x.i != N - 1) dfs(no{x.i, x.t - 1, x.b + 1, (x.k + 1) % K});
	for(ed e : adj[x.i]) {
		if(x.t < e.t) continue;
		dfs(no{e.v, x.t - e.t, x.b, x.k});
		if(x.b && e.v && e.v != N - 1) dfs({e.v, x.t - e.t, x.b - 1, x.k});
		if(x.b != B && e.v && e.v != N - 1) dfs({e.v, x.t - e.t, x.b + 1, x.k});
	}
	q.push_front(x);
}

inline void maxe(int &x, int val) {
	x = max(x, val);
}

void solve() {
	memset(seen, -1, sizeof seen);
	seen[0][T][0][0] = R;
	for(no x : q) {
		if(seen[x.i][x.t][x.b][x.k] < 0) continue;
		int d = seen[x.i][x.t][x.b][x.k];
		//printf("(%d, %d, %d, %d) = %d\n", x.i, x.t, x.b, x.k, d);
		maxe(seen[x.i][x.t - 1][x.b][x.k], d);
		maxe(seen[x.i][x.t - 1][x.b][(x.k + 1) % K], d);
		if(x.b && x.i && x.i != N - 1) maxe(seen[x.i][x.t - 1][x.b - 1][(x.k + 1) % K], d + p[(x.k + 1) % K][x.i]);
		if(x.b != B && x.i && x.i != N - 1 && d >= p[(x.k + 1) % K][x.i]) maxe(seen[x.i][x.t - 1][x.b + 1][(x.k + 1) % K], d - p[(x.k + 1) % K][x.i]);
		for(ed e : adj[x.i]) {
			if(x.t < e.t || d < e.m) continue;
			maxe(seen[e.v][x.t - e.t][x.b][x.k], d - e.m);
			if(x.b && e.v && e.v != N - 1) maxe(seen[e.v][x.t - e.t][x.b - 1][x.k], d - e.m + p[x.k][e.v]);
			if(x.b != B && e.v && e.v != N - 1 && d - e.m >= p[x.k][e.v]) maxe(seen[e.v][x.t - e.t][x.b + 1][x.k], d - e.m - p[x.k][e.v]);
		}
	}
}



int main() {
	int i, j, a, b, t, m;
	for_tests(tk, tt) {
		memset(seen, 0, sizeof seen); q.clear();
		scanf("%d %d %d %d %d %d", &N, &M, &B, &K, &R, &T);
		for(i = 0; i < K; i++)
			for(j = 0; j < N; j++)
				scanf("%d", &p[i][j]);
		for(i = 0; i < M; i++) {
			scanf("%d %d %d %d", &a, &b, &t, &m); a--; b--;
			adj[a].pb(ed{b, t, m});
		}
		printf("Case #%d: ", tt);
		dfs(no{0, T, 0, 0});
		solve();
		int x = seen[N - 1][0][0][0];
		if(x == -1) puts("Forever Alone");
		else printf("%d\n", x);
		for(i = 0; i < N; i++) adj[i].clear();
	}
}

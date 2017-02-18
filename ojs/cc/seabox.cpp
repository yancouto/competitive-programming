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

int en;
const int N = 41234;
vector<int> mn[N], mx[N];

void go(int u, int a, int b, int c, int sz) {
	if(sz == 1) { c1[u] = g[a][b][c]; val[u] = 1; return; }
	for(int i = a; i < a + sz; i += sz / 2)
		for(int j = b; j < b + sz; j += sz / 2)
			for(int k = c; k < c + sz; k += sz / 2) {
				int v = en++;
				go(v, i, j, k, sz / 2);
				c1[u] += c1[v];
				val[u] += val[v];
			}
	if(c1[u] == sz * sz * sz || c1[u] == 0)
		val[u] = 1;
}

void solve(int u, int a, int b, int c, int sz) {
	int S = sz * sz * sz;
	mn[u].resize(S + 1); mx[u].resize(S + 1);
	for(int i = 0; i <= S; i++) mn[u][i] = val[u], mx[u][i] = val[u];
	for(int i = min(c1[u], S - c1[u]); i <= S; i++)
		mn[u][i] = 1;
	if(sz == 1) { c1[u] = g[a][b][c]; return; }
	for(int i = a; i < a + sz; i += sz / 2)
		for(int j = b; j < b + sz; j += sz / 2)
			for(int k = c; k < c + sz; k += sz / 2) {
				int v = en++;
				solve(v, i, j, k, sz / 2);
				for(int g = 0; g <= S/8; g++)
					mn[u][g] = min(mn[u][i], mn[v][g] + mn[u][S - g]),
					mx[u][g] = min(mx[u][i], mx[v][g] + mx[u][S - g]);
			}
}

int main() {
	int i, j, k, K;
	scanf("%d %d", &n, &K);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			for(k = 0; k < n; k++)
				scanf("%d", &g[i][j][k]);
	go(en++, 0, 0, 0, n);
	en = 0;
	solve(en++, 0, 0, 0, n);
	printf("%d %d\n", mn[K], mx[K]);
}

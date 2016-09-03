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
const int N = 200;
int a[N][N];
int mn[N], mx[N], p[N], us[N], d[N];
vector<int> adj[N];
int seen[N];

int dfs(int u) {
	seen[u] = true;
	for(int v : adj[u]) {
		if(!seen[v])
			dfs(v);
		mx[u] = min(mx[u], mx[v] - 1);
	}
}

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	for(i = 0; i < n; i++) {
		int sum = accumulate(a[i], a[i] + n, 0);
		mx[i] = min(n - sum, n - 1);
	}
	for(j = 0; j < n; j++) {
		int sum = 0;
		for(i = 0; i < n; i++) sum += a[i][j];
		mn[j] = max(0, sum - 1);
		if(mn[j] > mx[j]) {
			puts("-1");
			return 0;
		}
		//printf("%d <= p[%d] <= %d\n", mn[j], j, mx[j]);
	}
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			if(i == j || !a[i][j]) continue;
			adj[i].pb(j);
			d[j]++;
		}
	for(i = 0; i < n; i++)
		if(!seen[i])
			dfs(i);
	for(i = 0; i < n; i++) {
		int k = -1;
		for(j = 0; j < n; j++)
			if(!us[j] && mn[j] <= i && mx[j] >= i && !d[j] && (k == -1 || mx[j] < mx[k]))
				k = j;
		if(k == -1) { puts("-1"); return 0; }
		for(int v : adj[k]) d[v]--;
		p[k] = i; us[k] = 1;
	}
	//for(i = 0; i < n; i++) printf("p[%d] = %d\n", i, p[i]);
	vector<pii> op;
	for(i = 0; i < n; i++) {
		if(us[i] == 2) continue;
		j = i;
		while(us[j] != 2) {
			us[j] = 2;
			if(p[j] != i) op.pb(pii(j + 1, p[j] + 1));
			j = p[j];
		}
	}
	printf("%d\n", (int) op.size());
	for(pii p : op)
		printf("%d %d\n", p.fst, p.snd);
}

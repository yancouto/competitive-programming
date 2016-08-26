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
const int N = 1123456;

int e[112345], s[112345];
int lc[101009][20];
int se[N], ans[N], id[N];
vector<int> adj[112345];

void dfs(int u, int p) {
	lc[u][0] = p;
	for(int i = 1; i < 18; i++)
		lc[u][i] = lc[lc[u][i - 1]][i - 1];
	for(int v : adj[u])
		dfs(v, u);
}

int main() {
	int i, n, q, ps, pe;
	scanf("%d %d", &n, &q);
	for(i = 0; i < N; i++) se[i] = INT_MAX;
	for(i = 0; i < n; i++) {
		scanf("%d %d", &s[i], &e[i]);
		if(e[i] < se[s[i]]) se[s[i]] = e[i], id[s[i]] = i;
	}
	s[n] = N - 1; e[n] = N - 1;
	id[N - 1] = n;
	ans[N - 1] = n;
	for(i = N - 2; i >= 1; i--) {
		ans[i] = ans[i + 1];
		if(se[i] != INT_MAX && se[i] < e[ans[i]]) {
			ans[i] = id[i];
			adj[ans[se[i] + 1]].pb(id[i]);
		}
	}
	dfs(n, n);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &ps, &pe);
		int u = ans[ps], ct = 0;
		for(int i = 17; i >= 0; i--)
			if(s[lc[u][i]] <= pe)
				u = lc[u][i], ct += (1 << i);
		if(e[u] <= pe) ct++;
		printf("%d\n", ct);
	}
}

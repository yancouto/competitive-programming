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
const int N = 1123;
char g[N][N];
int w[N], st[N], a[N];
vector<int> adj[N];

int main() {
	int i, j, n, sn;
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf(" %c", &g[i][j]);
		for(i = 0; i < n; i++) adj[i].clear(), a[i] = 0;
		for(i = 1; i < n; i++)
			if(g[0][i] == '0') {
				for(w[i] = 1; g[w[i]][i] == '0' || g[0][w[i]] == '0'; w[i]++);
				adj[w[i]].pb(i);
			}
		sn = 0;
		for(i = 1; i < n; i++)
			if(g[0][i] == '1' && !adj[i].empty())
				st[sn++] = i;
		sort(st, st + sn, [](int i, int j) { return adj[i].size() > adj[j].size(); });
		int cur = 0;
		for(j = 0; j < sn; j++) {
			i = st[j];
			a[cur++] = i+1;
			for(int x : adj[i]) a[cur++] = x+1;
			int k = 1 + adj[i].size();
			while(k & (k - 1)) k++, cur++;
		}
		a[cur] = 1;
		cur = 0;
		for(i = 1; i < n; i++)
			if(g[0][i] == '1' && adj[i].empty()) {
				for(; a[cur]; cur++);
				a[cur] = i+1;
			}
		for(j = 2; j <= n; j <<= 1)
			for(i = 0; i < (2*n)/j; i += 2) {
				printf("%d %d\n", a[i], a[i+1]);
				if(g[a[i]-1][a[i+1]-1] == '1') a[i/2] = a[i];
				else a[i/2] = a[i+1];
			}
		assert(a[0] == 1);
	}
}

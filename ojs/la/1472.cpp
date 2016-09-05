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
const int N = 1009;

int ord[N], on;
vector<int> adj[N], inv[N], e[N];
int seen[N];
bitset<N> at[N];

void go(int u) {
	seen[u] = true;
	for(int v : adj[u])
		if(!seen[v])
			go(v);
	ord[on++] = u;
}

int v[N], mrk[N];

int main() {
	int i, n, m, k, g, x, j;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		for(i = 0; i < n; i++) adj[i].clear(), inv[i].clear(), seen[i] = false, mrk[i] = -1;
		for(i = 0; i < m; i++) e[i].clear();
		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &v[i], &k, &g);
			at[i].reset();
			at[i][i] = 1;
			while(k--) {
				scanf("%d", &x); x--;
				adj[x].pb(i);
				inv[i].pb(x);
			}
			while(g--) {
				scanf("%d", &x); x--;
				e[x].pb(i);
			}
		}
		on = 0;
		for(i = 0; i < n; i++)
			if(!seen[i])
				go(i);
		reverse(ord, ord + n);
		for(i = 0; i < n; i++)
			for(int x : adj[ord[i]])
				v[x] += v[ord[i]];
		for(i = n - 1; i >= 0; i--)
			for(int x : adj[ord[i]])
				at[ord[i]] |= at[x];
		printf("*****\n");
		for(i = 0; i < m; i++) {
			int tot = 0;
			bitset<N> b;
			for(int x : e[i])
				b[x] = 1;
			for(j = 0; j < n; j++)
				if(b[j] && (b & at[j]).count() == 1)
					tot += v[j];
			printf("%d %d\n", i + 1, tot);
		}
	}
}

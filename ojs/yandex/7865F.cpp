#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

ll rnd() { return (ll(rand()) << 20) ^ (ll(rand()) << 32) ^ ll(rand()); }

const int N = 112345;
const int K = 5;

ll x[N];
int n;

void build(vector<int> adj[N], vector<ll> id[N]) {
	for(int i = 1; i <= n; i++) {
		id[i].resize(K);
		id[i][0] = x[adj[i].size()];
	}
	for(int k = 1; k < K; k++)
		for(int i = 1; i <= n; i++)
			for(int j : adj[i])
				id[i][k] ^= id[j][k - 1];
}

vector<ll> id[2][N];
vector<int> adj[2][N];
int p[2][N];
int mp[N];
int seen[2][N];

bool try_(int u0, int u1) {
	printf("try_(%d, %d)\n", u0, u1);
	mp[u1] = u0;
	seen[0][u0] = seen[1][u1] = 1;
	int sz = adj[0][u0].size();
	for(int i = 0; i < sz; ) {
		int j = i;
		while(j + 1 < sz && id[0][adj[0][u0][j + 1]] == id[0][adj[0][u0][i]]) {
			if(id[1][adj[1][u1][j + 1]] != id[0][adj[0][u0][i]]) {
				seen[0][u0] = seen[1][u1] = 0;
				return false;
			}
			for(int k = i; k <= j; k++)
				if(!seen[0][adj[0][u0][k]] && !try_(adj[0][u0][k], adj[1][u1][k])) {
					seen[0][u0] = seen[1][u1] = 0;
					return false;
				}
			j++;
		}
		i = j + 1;
	}
	printf("try_(%d, %d)\n", u0, u1);
	return true;
}

int main() {
	srand(2012);
	int i, j, m;
	scanf("%d %d", &n, &m);
	for(i = 1; i <= n; i++)
		x[i] = rnd();
	for(i = 1; i <= n; i++)
		for(j = i + i; j <= n; j += i)
			adj[0][i].pb(j), adj[0][j].pb(i);
	for(i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[1][a].pb(b);
		adj[1][b].pb(a);
	}
	build(adj[0], id[0]);
	build(adj[1], id[1]);
	for(i = 1; i <= n; i++) p[0][i] = p[1][i] = i;
	sort(p[0] + 1, p[0] + n + 1, [](int i, int j) { return id[0][i] < id[0][j]; });
	sort(p[1] + 1, p[1] + n + 1, [](int i, int j) { return id[1][i] < id[1][j]; });
	for(i = 1; i <= n; i++) {
		sort(adj[0][i].begin(), adj[0][i].end(), [](int a, int b) { return id[0][a] < id[0][b]; });
		sort(adj[1][i].begin(), adj[1][i].end(), [](int a, int b) { return id[1][a] < id[1][b]; });
	}
	for(i = 1; i <= n; ) {
		int j = i;
		while(j + 1 <= n && id[0][p[0][i]] == id[0][p[0][j + 1]]) j++;
		printf("[%d, %d]\n", i, j);
		vector<int> lef;
		for(int k = i; k <= j; k++)
			if(!seen[1][p[1][k]])
				lef.pb(p[1][k]);
		for(int k = i; k <= j; k++) {
			if(seen[0][p[0][k]]) continue;
			for(int g : lef)
				if(try_(p[0][k], g))
					break;
			vector<int> l2;
			for(int g : lef)
				if(!seen[1][p[1][k]])
					l2.pb(g);
			lef = l2;
		}
		i = j + 1;
	}
	for(i = 1; i <= n; i++)
		printf("%d ", mp[i]);
	putchar('\n');
}

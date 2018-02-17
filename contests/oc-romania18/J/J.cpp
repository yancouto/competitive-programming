#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 2509;
int pw[N][N * 2];
int ch[N * 2][N];
ll ans;
#define fst first
#define snd second
ll sz[N];
vector<pii> adj[N];

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int n, m;

int go(int u, int p, ll l) {
	sz[u] = 1;
	for(pii e : adj[u])
		if(e.fst != p)
			sz[u] += go(e.fst, u, e.snd);
	if(u) {
		//printf("%d sz %lld\n", u, sz[u]);
		for(int i = 0; i <= 2 * m; i++) {
			ll cur = mod(ll(pw[sz[u]][i]) * ll(pw[n - sz[u]][2 * m - i]));
			cur = mod(cur * ll(ch[2 * m][min(i, 2 * m - i)]));
			//printf("[%d] cur %lld * %lld * %lld\n", i, cur, l, min<ll>(i, 2 * m - i));
			ans = mod(ans + cur * mod(l * min<ll>(i, 2 * m - i)));
		}
	}
	return sz[u];
}

int main () {
	for(int i = 0; i < N; i++) {
		pw[i][0] = 1;
		for(int j = 1; j < N * 2; j++)
			pw[i][j] = mod(ll(pw[i][j - 1]) * ll(i));
	}
	ch[0][0] = 1;
	for(int i = 1; i < 2 * N; i++) {
		ch[i][0] = 1;
		for(int j = 1; j < N; j++)
			ch[i][j] = mod(ch[i - 1][j] + ch[i - 1][j - 1]);
	}
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n - 1; i++) {
		int a, b, l;
		scanf("%d %d %d", &a, &b, &l); a--; b--;
		adj[a].pb(pii(b, l));
		adj[b].pb(pii(a, l));
	}
	go(0, 0, -1);
	printf("%lld\n", ans);
}

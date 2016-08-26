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

vector<pii> adj[N];
int n;
int memo[N][N];
int solve(int u, int k) {
	if(u == n - 1) return k? 100000000 : 0;
	if(k == 0) return 100000000;
	int &r = memo[u][k];
	if(r != -1) return r;
	r = INT_MAX;
	for(pii e : adj[u])
		r = min(r, e.snd + solve(e.fst, k - 1));
	return r;
}

double p, p1;
bool seen[N][N];
bool seen2[N][N];
double memo2[N][N];
double want(int i, int all) {
	if(all == 0) return i == 0;
	double &r = memo2[i][all];
	if(seen[i][all]) return r;
	seen[i][all] = true;
	return r = p1 * want(i - 1, all - 1) + (1. - p1) * want(i, all - 1);
}

double memo3[N][N];
double prob(int i, int all) {
	if(i >= all) return want(i, all);
	double &r = memo2[i][all];
	if(seen2[i][all]) return r;
	return r = prob(i + 1, all) + want(i, all);
}

int pn = 0;
void build(int u, int k) {
	pn++;
	printf("%d ", u + 1);
	if(u == n - 1) return;
	for(pii e : adj[u])
		if(solve(u, k) == e.snd + solve(e.fst, k - 1))
			return build(e.fst, k - 1);
}

int main() {
	int i, m, a, b, c, j;
	memset(memo, -1, sizeof memo);
	scanf("%d %d", &n, &m);
	scanf("%lf %lf", &p, &p1);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c); a--; b--;
		adj[a].pb(pii(b, c));
		adj[b].pb(pii(a, c));
	}
	double best = 1/0.; int bi;
	for(i = n; i > 1; i--) {
		int C = solve(0, i - 1);
		if(C >= 100000000) continue;
		//for(j = 0; j < i && prob(j+1, i) > 1.-p; j++);
		double l = 0, r = 24 * i;
		for(j = 0; j < 100; j++) {
			double m = (l + r) / 2.;
			if(prob(int(m / 24) + 1, i) <= 1. - p) r = m;
			else l = m;
		}
		if(C + l <= best) {
			best = C + l;
			bi = i;
		}
	}
	printf("%d\n", bi);
	build(0, bi - 1);
	putchar('\n');
	assert(pn == bi);
}

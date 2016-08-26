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
const int N = 112345;

vector<pii> adj[2][N];
int dist[2][N], seen[N];
ll acc[N];

void solve(int d, int u) {
	priority_queue<pii> pq;
	pq.push(pii(0, u));
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(seen[x.snd] == d + 1) continue;
		seen[x.snd] = d + 1;
		dist[d][x.snd] = -x.fst;
		for(pii e : adj[d][x.snd])
			pq.push(pii(x.fst - e.snd, e.fst));
	}
}

ll memo[112345][2];
ll& dp(int i, int s) { return memo[i][s & 1]; }

void rec(int s, int l, int r, int opl, int opr) {
	if(l > r) return;
	int m = (l + r) / 2;
	ll best = LLONG_MAX; int op;
	for(int k = max(opl, m); k <= opr; k++) {
		ll v = ll(k - m) * ll(acc[k] - (m? acc[m - 1] : 0ll)) + dp(k + 1, s - 1);
		if(v <= best) { best = v; op = k; }
	}
	assert(best < 3e17 && best >= 0);
	dp(m, s) = best;
	rec(s, l, m - 1, opl, op);
	rec(s, m + 1, r, op, opr);
}


int main() {
	int n, b, s, r, u, v, l, i;
	scanf("%d %d %d %d", &n, &b, &s, &r);
	for(i = 0; i < r; i++) {
		scanf("%d %d %d", &u, &v, &l); u--, v--;
		adj[0][u].pb(pii(v, l));
		adj[1][v].pb(pii(u, l));
	}
	solve(0, b); solve(1, b);
	for(i = 0; i < b; i++)
		acc[i] = ll(dist[0][i] + dist[1][i]);
	sort(acc, acc + b);
	for(i = 1; i < b; i++)
		acc[i] += acc[i - 1];
	for(i = 0; i < b; i++)
		dp(i, 0) = 3e17;
	for(i = 1; i <= s; i++)
		rec(i, 0, b-1, 0, b-1);
	printf("%lld\n", dp(0, s));
}

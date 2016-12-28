#include <bits/stdc++.h>
using namespace std;
#define t first
#define dt second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 321, M = 11234;
int dn, W;
ll w[N], t[N], dt[N];
double acc[M];

ll solve(int,int);
ll calc(int i, int s, ll m) {
	if(solve(i + 1, s - m * w[i]) == LLONG_MIN) return LLONG_MIN;
	return solve(i + 1, s - m * w[i]) + m * t[i] - ((ll(m) * ll(m - 1)) / 2ll) * dt[i];
}

ll memo[312][11234];
ll solve(int i, int s) {
	if(s == 0) return 0;
	if(i == dn) return LLONG_MIN;
	if(memo[i][s] != -1) return memo[i][s];
	memo[i][s] = LLONG_MIN;
	int l = 0, r = s / w[i];
	while(l < r) {
		ll m = (l + r) / 2;
		if(calc(i, s, m) <= calc(i, s, m + 1)) l = m + 1;
		else r = m;
	}
	return memo[i][s] = calc(i, s, l);
}


typedef pair<double, double> pdd;
int main() {
	memset(memo, -1, sizeof memo);
	int i, d, w, t, dt; char op;
	vector<pdd> pq;
	scanf("%d %d", &d, &W);
	for(i = 0; i < d; i++) {
		scanf(" %c", &op);
		if(op == 'D') {
			scanf("%d %d %d", &w, &t, &dt);
			::w[dn] = w;
			::t[dn] = t;
			::dt[dn++] = dt;
		} else {
			scanf("%d %d", &t, &dt);
			pq.pb(pdd(t, dt));
		}
	}
	if(pq.empty()) {
		if(solve(0, W) <= LLONG_MIN) puts("impossible");
		else printf("%lld\n", solve(0, W));
		return 0;
	}

	////////////////
	sort(pq.begin(), pq.end());
	double ans = 0;
	for(i = 1; i <= W; i++) {
		double left = 1;
		pdd g = pq.back(); pq.pop_back();
		while(g.dt > 0 && !pq.empty() && g.t - left * g.dt < pq.back().t) {
			double n = (g.t - pq.back().t) / g.dt;
			ans += n * g.t - (n * n / 2.) * g.dt;
			g.dt = (g.dt * pq.back().dt) / (g.dt + pq.back().dt);
			g.t = pq.back().t;
			pq.pop_back();
			left -= n;
		}
		double n = left;
		ans += n * g.t - (n * n / 2.) * g.dt;
		g.t -= n * g.dt;
		pq.pb(g);
		acc[i] = ans;
	}
	////////////////

	double best = -1./0.;
	for(i = W; i >= 0; i--) {
		ll ans = solve(0, i);
		if(ans <= LLONG_MIN) continue;
		best = max(best, (double) ans + acc[W - i]);
	}
	printf("%.10f\n", best);
}

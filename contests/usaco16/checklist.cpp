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

inline ll sqr(ll x) { return x * x; }
inline ll dist(ll x1, ll y1, ll x2, ll y2) { return sqr(x2 - x1) + sqr(y2 - y1); }

const int N = 1009;
int h, g, xh[N], yh[N], xg[N], yg[N];
ll memo[N][N][2];
ll solve(int i, int j, bool l) {
	if(i == h) return 0;
	ll &r = memo[i][j][l];
	if(r != -1) return r;
	r = LLONG_MAX;
	int cx = (l? xh[i - 1] : xg[j - 1]);
	int cy = (l? yh[i - 1] : yg[j - 1]);
	if(i < h && (i < h - 1 || j == g)) r = solve(i + 1, j, true) + dist(cx, cy, xh[i], yh[i]);
	if(j < g) r = min(r, solve(i, j + 1, false) + dist(cx, cy, xg[j], yg[j]));
	return r;
}

int main() {
	freopen("checklist.in", "r", stdin);
	freopen("checklist.out", "w", stdout);
	int i;
	memset(memo, -1, sizeof memo);
	scanf("%d %d", &h, &g);
	for(i = 0; i < h; i++) scanf("%d %d", &xh[i], &yh[i]);
	for(i = 0; i < g; i++) scanf("%d %d", &xg[i], &yg[i]);
	printf("%lld\n", solve(1, 0, true));
}

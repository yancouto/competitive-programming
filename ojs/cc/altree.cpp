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

int n;
int es[2][18][18];
ll memo[1 << 18][18][2];
ll solve(int bm, int lst, bool co) {
	if(bm == (1 << n) - 1) return 0;
	ll &r = memo[bm][lst][co];
	if(r != 0) return r;
	r = 1e15;
	for(int i = 0; i < n; i++) {
		if((bm >> i) & 1) continue;
		pii e(i, lst);
		if(e.fst > e.snd) swap(e.fst, e.snd);
		if(es[co][e.fst][e.snd]) r = min(r, es[co][e.fst][e.snd] + solve(bm | (1 << i), i, !co));
	}
	return r;
}

int main() {
	int i, m, a, b, w; char c;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d %c", &a, &b, &w, &c); a--; b--;
		if(a > b) swap(a, b);
		int &v = es[c == 'B'][a][b];
		if(v) v = min(v, w);
		else v = w;
	}
	ll mn = LLONG_MAX;
	for(i = 0; i < n; i++)
		mn = min(mn, min(solve(1 << i, i, 0), solve(1 << i, i, 1)));
	if(mn > 1e14) printf("-1\n");
	else printf("%lld\n", mn);
}

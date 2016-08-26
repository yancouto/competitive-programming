#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
pii a[203];

ll memo2[202][202];
ll sum(int x, int y) {
	ll &r = memo2[x][y];
	if(r != -1) return r;
	r = 0;
	for(int i = x + 1; i < y; i++)
		r += min(a[i].fst - a[x].fst + a[x].snd, a[y].fst - a[i].fst + a[y].snd);
	return r;
}

int n;
ll memo[202][40];
ll solve(int d, int k) {
	if(d == n - 1) return 0;
	ll &r = memo[d][k];
	if(r != -1) return r;
	if(k == 0) {
		r = 0;
		for(int i = d + 1; i < n; i++)
			r += a[i].fst - a[d].fst + a[d].snd;
		return r;
	}
	r = LLONG_MAX;
	for(int i = d + 1; i < n; i++)
		r = min(r, sum(d, i) + solve(i, k - 1));
	return r;
}

int main() {
	int k, i, j;
	for_tests(t, tt) {
		scanf("%d %d", &n, &k);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i].fst);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i].snd);
		sort(a, a + n);
		memset(memo, -1, sizeof memo);
		memset(memo2, -1, sizeof memo2);
		ll mn = LLONG_MAX;
		for(i = 0; i < n; i++) {
			ll val = 0;
			for(j = 0; j < i; j++)
				val += a[i].fst - a[j].fst + a[i].snd;
			mn = min(mn, val + solve(i, k - 1));
		}
		printf("%lld\n", mn);
	}
}

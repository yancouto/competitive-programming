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
int a[202];
ll m2[201][201][201];
ll sum(int i, int j, int k) {
	if(i == j) return 0;
	ll &r = m2[i][j][k];
	if(r == -1) r = ll(min(a[k] - a[j], a[j] - a[i])) + sum(i, j - 1, k);
	return r;
}

const ll inf = 100000000000000000;
int n;
ll memo[202][32];
ll solve(int di, int k) {
	if(di >= n) return inf;
	ll &r = memo[di][k];
	if(r != -1) return r;
	r = 0; int i;
	if(k == 0) {
		for(i = di + 1; i < n; i++)
			r += a[i] - a[di];
		return r;
	}
	r = inf;
	for(i = di + 1; i < n; i++)
		r = min(r, sum(di, i - 1, i) + solve(i, k - 1));
	return r;
}

int rn;
void build(int di, int k, int fst) {
	printf("Depot %d at restaurant %d serves restaurant", ++rn, di + 1);
	int lst, i = 0, j;
	if(k) {
		for(i = di + 1; i < n; i++)
			if(solve(di, k) == sum(di, i - 1, i) + solve(i, k - 1)) {
				for(j = di + 1; j < i; j++)
					if(a[i] - a[j] < a[j] - a[di])
						break;
				lst = j - 1;
				break;
			}
	}
	else  lst = n - 1;
	if(lst > fst) printf("s %d to %d\n", fst + 1, lst + 1);
	else printf(" %d\n", fst + 1);
	if(i) build(i, k - 1, lst + 1);
}

int main() {
	int i, j, k, K, t = 0;
	while(true) {
		scanf("%d %d", &n, &K);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++)
				for(k = i; k < j; k++)
					m2[i][k][j] = -1;
		memset(memo, -1, sizeof memo);
		ll r = LLONG_MAX; int fst;
		for(i = 0; i < n; i++) {
			ll x = 0;
			for(j = 0; j < i; j++) x += ll(a[i] - a[j]);
			if(x + solve(i, K - 1) < r) fst = i;
			r = min(r, x + solve(i, K - 1));
		}
		rn = 0;
		printf("Chain %d\n", ++t);
		build(fst, K - 1, 0);
		printf("Total distance sum = %lld\n\n", r);
	}
}

#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

ll memo3[59][59];
ll pd2(int k, int n) {
	if(k == 0) return 1;
	if(n == 0) return 0;
	ll &r = memo3[k][n];
	if(r != -1) return r;
	r = mod(pd2(k, n - 1) + pd2(k - 1, n));
	printf("pd2(%d, %d) = %lld\n", k, n, r);
	return r;
}

ll memo2[59][59][59];
ll pd(int sz, int n, int s) {
	if(n == 0) return 1;
	ll &r = memo2[sz][n][s];
	if(r != -1) return r;
	r = 0;
	//printf("pd(%d, %d, %d) = %lld\n", sz, n, s, r);
	for(int i = 1; i < s; i++) {
		ll tmp = 1;
		for(int j = 1; i * j <= n; j++) {
			tmp = mod(tmp * pd(1, i - 1, i));
			r = mod(r + tmp * mod(pd(sz, n - i * j, i) * pd2(j, sz)));
		}
	}
	printf("pd(%d, %d, %d) = %lld\n", sz, n, s, r);
	return r;
}

ll memo[59][59][59];
ll all(int n, int rs, int s) {
	if(n == 0) return 1;
	ll &r = memo[n][rs][s];
	if(r != -1) return r;
	r = 0;
	for(int ro = 1; ro <= rs && ro <= n; ro++)
		for(int i = ro; i < (ro == rs? s : n + 1) && i <= n; i++) {
			ll tmp = 1;
			for(int j = 1; i * j <= n; j++) {
				tmp = mod(tmp * pd(ro, i - ro, i));
				r = mod(r + tmp * all(n - i * j, ro, i));
			}
		}
	printf("all(%d, %d, %d) = %lld\n", n, rs, s, r);
	return r;
}

int main() {
	memset(memo, -1, sizeof memo);
	memset(memo2, -1, sizeof memo2);
	memset(memo3, -1, sizeof memo3);
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j;
	scanf("%d %lld", &n, &modn);
	printf("%d\n", (int) all(n, n + 1, n + 1));
}

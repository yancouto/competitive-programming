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


ll memo[502][502];
ll choose(int n, int p) {
	if(n < 0 || p > n || p < 0) return 0;
	if(n == 0) return 1;
	ll &r = memo[n][p];
	if(r == -1) r = mod(choose(n - 1, p) + choose(n - 1, p - 1));
	return r;
}

int main() {
	int i, n, m, k, d, x;
	memset(memo, -1, sizeof memo);
	for_tests(t, tt) {
		scanf("%d %d %d %d", &n, &m, &k, &d);
		int go = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			if(x >= d) go++;
		}
		ll ans = 0;
		for(i = k; i <= go; i++)
			ans = mod(ans + choose(go, i) * choose(n - go, m - i));
		printf("%d\n", (int) ans);
	}
}

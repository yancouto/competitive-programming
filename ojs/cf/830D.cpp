#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

ll memo[412];
ll dp(int n) {
	if(n == 1) return 1;
	ll &r = memo[n];
	if(r != -1) return r;
	r = mod(1ll + 6ll * dp(n - 1) + 2ll * dp(n - 1) * dp(n - 1));
	return r;
}

int main() {
	memset(memo, -1, sizeof memo);
	int i, j;
	scanf("%d", &n);
	printf("%lld\n", dp(n));
}

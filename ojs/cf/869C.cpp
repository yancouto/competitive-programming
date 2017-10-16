#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 998244353;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

const int N = 5123;

ll fat[N], ifat[N];

ll choose(ll n, ll p) {
	return mod(fat[n] * mod(ifat[p] * ifat[n - p]));
}

ll go(ll a, ll b) {
	ll ans = 0;
	for(int i = 0; i <= min(a, b); i++)
		ans = mod(ans + choose(a, i) * mod(choose(b, i) * fat[i]));
	return ans;
}

ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1) {
		if(p & 1) r = mod(r * x);
		x = mod(x * x);
	}
	return r;
}

int main() {
	int i, j;
	fat[0] = 1;
	for(i = 1; i < N; i++) fat[i] = mod(fat[i - 1] * ll(i));
	for(i = 0; i < N; i++) ifat[i] = fexp(fat[i], modn - 2);
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	ll ans = 1;
	ans = mod(ans * go(a, b));
	ans = mod(ans * go(b, c));
	ans = mod(ans * go(c, a));
	printf("%lld\n", ans);
}

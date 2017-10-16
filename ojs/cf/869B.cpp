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
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

int main() {
	ll a, b;
	scanf("%lld %lld", &a, &b);
	if(a == b) { puts("1"); return 0; }
	ll ans = 1;
	for(ll x = a + 1; x <= b && ans != 0; x++)
		ans = (ans * (x % 10ll)) % 10ll;
	printf("%lld\n", ans);
}

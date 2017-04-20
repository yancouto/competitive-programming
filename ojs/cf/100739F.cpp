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

inline ll low(ll k) { return k * (k + 1ll) / 2ll; }
inline ll high(ll n, ll k) { return (n + n - k + 1ll) * k / 2ll; }


void go(ll n, ll p, ll q) {
	if(p < low(q) || p > high(n, q)) return;
	ll i = 1 + (p - low(q)) / q;
	ll beg = q - ((p - low(q)) % q);
	while(beg--) printf("%d ", i++), q--;
	i++;
	while(q--) printf("%d ", i++);
	putchar('\n');
	exit(0);
}

int main() {
	int i, j, n, q; ll p;
	scanf("%d %lld %d", &n, &p, &q);
	for(i = 1; q * i <= n; i++)
		go(n, p * i, q * i);
	puts("IMPOSSIBLE");
}

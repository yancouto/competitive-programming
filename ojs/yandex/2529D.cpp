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

const int N = 2123456;
int b, g, p;
ll fat[N], inv[N];
inline ll comb(int n, int p) {
	if(p > n || p < 0) return 0ll;
	return mod(fat[n] * mod(inv[p] * inv[n - p]));
}

ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			r = mod(r * x);
	return r;
}

ll calc(int k) {
	if(k == 1) {
		if(min(b, g) > 0) return 0;
		return fat[b + g];
	}
	ll tot = mod(comb(p, k - 1) * fat[k - 1]); // pares
	tot = mod(tot * fat[b - (k - 1)]); // boys
	tot = mod(tot * fat[g - (k - 1)]); // girls
	ll bo = mod(tot * mod(comb(b - (k - 1) + ((k + 1) / 2) - 1, ((k + 1) / 2) - 1) * comb(g - (k - 1) + (k / 2) - 1, (k / 2) - 1)));
	ll gi = mod(tot * mod(comb(b - (k - 1) + (k / 2) - 1, (k / 2) - 1) * comb(g - (k - 1) + ((k + 1) / 2) - 1, ((k + 1) / 2) - 1)));
	return mod(bo + gi);
}

int main() {
	int i;
	fat[0] = 1;
	for(i = 1; i < N; i++)
		fat[i] = mod(ll(i) * fat[i - 1]);
	inv[N - 1] = fexp(fat[N - 1], modn - 2);
	for(i = N - 2; i >= 0; i--) inv[i] = mod(inv[i + 1] * ll(i + 1));
	scanf("%d %d %d", &b, &g, &p);
	ll tot = 0;
	for(i = 1; i <= p + 1; i++)
		tot = mod(tot + calc(i));
	printf("%d\n", (int) mod(tot));
}

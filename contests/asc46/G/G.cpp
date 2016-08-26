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
const ll modn = 242121643;
inline ll mod(ll x) { return x % modn; }
const int M = 209;

ll fexp(ll x, ll p) {
	ll ans = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			ans = mod(ans * x);
	return ans;
}

ll p2[M], fat[M], invf[M];
ll comb(int n, int p) {
	if(n < 0 || p < 0 || p > n) return 0;
	return mod(fat[n] * mod(invf[p] * invf[n - p]));
}

int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	fat[0] = 1;
	invf[0] = 1;
	for(int i = 1; i < M; i++)
		fat[i] = mod(ll(i) * fat[i - 1]),
		invf[i] = fexp(fat[i], modn - 2);
	int n, k, no, n1, x;
	while(scanf("%d %d", &n, &k) != EOF && n) {
		no = n1 = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d", &x);
			if(x == 1) n1++;
			else no++;
		}
		ll tot = 0;
		for(int i = 1; i <= k && i <= n1; i += 2)
			tot = mod(tot + comb(n1, i) * comb(no, k - i));
		printf("%d\n", (int) tot);
	}
}

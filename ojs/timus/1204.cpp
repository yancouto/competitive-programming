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

ll fexp(ll n, ll p, ll mod) {
	ll r = 1;
	for(; p; p >>= 1, n = (n * n) % mod)
		if(p & 1)
			r = (r * n) % mod;
	return r;
}

inline ll chinese(ll fp, ll a, ll p, ll fq, ll b, ll q) {
	return (b * fexp(p, fq, p * q) + a * fexp(q, fp, p * q)) % (p * q);
}



int main() {
	int i, n, j;
	for_tests(t, tt) {
		scanf("%d", &n);
		vector<int> d;
		vector<int> f;
		for(i = 2; i * i <= n; i++) {
			if(n % i) continue;
			int x = 1;
			while(!(n % i)) n /= i, x *= i;
			d.pb(x);
			f.pb(x - x/i);
		}
		if(n > 1) d.pb(n), f.pb(n - 1);
		n = d.size();
		vector<int> ans;
		for(i = 0; i < (1 << n); i++) {
			int x = i & 1, m = d[0], phi = f[0];
			for(j = 1; j < n; j++) {
				x = chinese(phi, x, m, f[j], (i >> j) & 1, d[j]);
				m *= d[j]; phi *= f[j];
			}
			ans.pb(x);
		}
		sort(ans.begin(), ans.end());
		for(int x : ans) printf("%d ", x);
		printf("\n");
	}
}

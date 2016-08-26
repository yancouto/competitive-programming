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
const int N = 1000009;

ll p[N], pe[N], phi[N], pref[N];
ll n, k;

ll fexp(ll n, ll p, ll mod) {
	ll r = 1 % mod;
	for(; p; p >>= 1, n = (n * n) % mod)
		if(p & 1)
			r = (r * n) % mod;
	return r;
}

void join(ll &r, ll &m, int i, ll val) {
	//printf("X = %lld mod %lld\nX = %lld mod %lld\n", r, m, val, pe[i]);
	ll nm = m * pe[i];
	//printf("%lld ^ %lld %% %lld = %lld\n", m, phi[i], nm, fexp(m , phi[i], nm));
	r = ((((val - r) % nm) + nm) * fexp(m, phi[i], nm) + r) % nm;
	m = nm;
	//printf("->X = %lld mod %lld\n", r, m);
}

void pre(int i) {
	pref[0] = 1;
	for(ll k = 1; k < pe[i]; k++) {
		ll x = k;
		while(!(x % p[i])) x = 1;
		pref[k] = (pref[k - 1] * x) % pe[i];
		//printf("pre[%lld] = %lld\n", k, pref[k]);
	}
}

inline ll inv(ll n, int i) { return fexp(n, phi[i] - 1, pe[i]); }

ll fat(ll n, int i) {
	if(n < p[i]) return pref[n];
	ll val = fexp(pref[pe[i] - 1], n / pe[i], pe[i]);
	val = (val * pref[n % pe[i]]) % pe[i];
	return (val * fat(n / p[i], i)) % pe[i];
}

ll solve(int i) {
	//printf("solve for i%d p%lld pe%lld phi%lld\n", i, p[i], pe[i], phi[i]);
	ll pqtd = 0;
	ll pp = 1;
	while(log(pp) + log(p[i]) < log(2) + 18. * log(10)) {
		pp *= p[i];
		pqtd += n / pp;
		pqtd -= ((n - k) / pp) + (k / pp);
	}
	//printf("(%lld %lld) has %lld ps\n", n, k, pqtd);
	ll val = (fat(n, i) * inv(fat(n - k, i), i)) % pe[i];
	val = (val * inv(fat(k, i), i)) % pe[i];
	val = (val * fexp(p[i], pqtd, pe[i])) % pe[i];
	//printf("(%lld %lld) %% %lld = %lld\n", n, k, pe[i], val);
	return val;
}

int main() {
	ll m; int i; int pn = 0;
	scanf("%lld %lld %lld", &n, &k, &m);
	for(i = 2; i * i <= m; i++) {
		if(m % i) continue;
		int P = 1;
		while(!(m % i)) m /= i, P *= i;
		p[pn] = i;
		pe[pn] = P;
		phi[pn++] = P - (P / i);
	}
	if(m != 1) p[pn] = pe[pn] = m, phi[pn++] = m - 1;
	ll r = 0; m = 1;
	for(i = 0; i < pn; i++) {
		pre(i);
		join(r, m, i, solve(i));
	}
	printf("%lld\n", r);
}

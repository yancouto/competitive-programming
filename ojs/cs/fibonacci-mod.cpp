#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
ll M = 1000000007;
inline ll mod(ll x) { return x % M; }

ll A[2][2], B[2][2], C[2][2];

inline void cp(ll from[2][2], ll to[2][2]) {
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			to[i][j] = from[i][j];
}

inline void mul(ll A[2][2], ll B[2][2], ll C[2][2]) {
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			C[i][j] = mod(A[i][0] * B[0][j] + A[i][1] * B[1][j]);
}

ll R[2][2], X[2][2];
ll FM[60][2][2];

pii calc(ll k) {
	ll f0 = 0, f1 = 1;
	//printf("calk(%lld) = ", k);
	while(k != 0) {
		int i = __builtin_ctzll(k);
		assert(i < 60);
		ll nf0 = mod(f0 * FM[i][0][0] + f1 * FM[i][1][0]);
		ll nf1 = mod(f0 * FM[i][0][1] + f1 * FM[i][1][1]);
		f0 = nf0;
		f1 = nf1;
		assert(k & (1ll << i));
		k ^= (1ll << i);
	}
	//printf("(%lld, %lld)\n", f0, f1);
	return pii(f0, f1);
}

inline bool test(ll x) {
	//printf("test(%lld)\n", x);
	return calc(x) == pii(0, 1);
}

inline ll rnd() {
	return (rand() ^ (ll(rand()) << 30)) % ll(1.5e10);
}
struct st { pii x; ll v; bool operator < (st o) const { return x < o.x; } };

st vec[112345], all[112345];
int p1[112345], p2[112345];
int vn, an;
unordered_set<ll> tst[6];
unordered_map<ll, ll> ans[6];

inline ll join(ll a, ll b) { return (a << 30) + b; }
inline ll join(pii x) { return join(x.fst, x.snd); }

int main() {
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			FM[0][i][j] = (i || j);
	for_tests(tn, tt) {
		vn = an = 0;
		ll a, b;
		scanf("%lld %lld %lld", &M, &a, &b);
		for(int i = 1; i < 60; i++)
			mul(FM[i - 1], FM[i - 1], FM[i]);
		unordered_set<ll> &tst = ::tst[tt];
		tst.reserve(50000);
		unordered_map<ll, ll> &ans = ::ans[tt];
		ll mul;
		while(true) {
			ll x = rnd();
			if(tst.count(x)) continue;
			tst.insert(x);
			ll f = join(calc(x));
			//printf("%lld -> (%lld, %lld)\n", x, f.fst, f.snd);
			if(ans.count(f)) {
				mul = abs(ans[f] - x);
				break;
			} else
				ans[f] = x;
		}
		//printf("done mul = %lld\n", mul);
		ll sz = -1;
		ll d;
		for(d = 1; d * d <= mul; d++) {
			if(sz == -1 && !(mul % d) && test(d)) {
				sz = d;
				break;
			}
		}
		while(d * d > mul) d--;
		for(; d >= 1; d--) {
			if(sz == -1 && !(mul % d) && test(mul / d)) {
				sz = mul/d;
				break;
			}
		}
		//printf("sz %lld\n", sz);
		assert(sz != -1);
		int sq = sqrt(sz) + .5;
		//printf("sq %d\n", sq);
		unordered_map<ll, ll> mp;
		mp.reserve(500000);
		for(int i = 0; i < sz; i += sq) {
			//p1[vn] = vn;
		    //vec[vn++] = st{calc(i), i};
			mp[join(calc(i))] = i;
		}
		//sort(vec.begin(), vec.end());
		int ct;
		for(ct = 0; ct < sq + 5; ct++) {
			if(mp.count(join(a, b))) break;
			//p2[an] = an;
			//all[an++] = st{pii(a, b), ct};
			a = (a + b) % M;
			swap(a, b);
		}
		if(ct == sq + 5) { puts("-1"); continue; }
		printf("%lld\n", (mp[join(a, b)] - ct + sz) % sz);
		continue;
		//sort(p1, p1 + vn, [](int i, int j) { return vec[i] < vec[j]; });
		//sort(p2, p2 + an, [](int i, int j) { return all[i] < all[j]; });
		int i = 0; int j = 0;
		while(i < an && j < vn) {
			if(all[p2[i]].x == vec[p1[j]].x) break;
			if(all[p2[i]].x < vec[p1[j]].x) i++;
			else j++;
		}
		if(i == an || j == vn) { puts("-1"); continue; }
		//printf("after %d hit (%lld, %lld) = %lld\n", ct, a, b, ans[pii(a, b)]);
		printf("%lld\n", (vec[p1[j]].v - (all[p2[i]].v % sz) + sz) % sz);
	}
}

#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, int> pii;
typedef pair<int, ll> pil;

#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
#define div askjdasld
const int N = 1123;
ll a[N]; int n; ll pre[N];
vector<ll> div, ps;
int ct[N][15];
int cd[7123][15];
ll p[15][41];

inline ll gcd(int d, int i) {
	ll a = 1;
	for(int j = 0; j < ps.size(); j++)
		a *= p[j][min(cd[d][j], ct[i][j])];
	return a;
}

pil mp[N][6800];
pil solve(int i, ll k) {
	if(k == 1) return pil(0, 0);
	if(i == n) return pil(1e5, 1e5);
	int ki = lower_bound(div.begin(), div.end(), k) - div.begin();
	if(mp[i][ki].snd) return mp[i][ki];
	pil &r = mp[i][ki];
	r = solve(i + 1, k);
	ll nk = k / gcd(ki, i);
	pil q = solve(i + 1, nk); q.fst++; q.snd += a[i];
	r = min(r, q);
	return r;
}

vector<int> best;
ll gcdt(ll a, ll b) {
	if(!b) return a;
	return gcdt(b, a % b);
}

void build(int i, ll k) {
	if(k == 1) {
		printf("%d\n", (int) best.size());
		for(int id : best) printf("%d ", id+1);
		printf("\n");
		exit(0);
	}
	if(solve(i, k) == solve(i + 1, k))
		build(i + 1, k);
	else {
		best.pb(i);
		build(i + 1, k / gcdt(k, a[i]));
	}
}

int main() {
	int i, j; ll k;
	scanf("%d %lld", &n, &k);
	n = 1000; k = 963761198400ll;
	for(ll i = 1; i * i <= k; i++) {
		if(!(k % i)) div.pb(i);
		if(!(k % i) && i * i < k) div.pb(k / i);
	}
	sort(div.begin(), div.end());
	ll ok = k;
	for(ll i = 2; i * i <= k; i++) {
		if(ok % i) continue;
		while(!(ok % i)) ok /= i;
		ps.pb(i);
	}
	if(ok > 1) ps.pb(ok);
	for(i = 0; i < ps.size(); i++) {
		p[i][0] = 1;
		for(j = 1; j < 41; j++)
			p[i][j] = p[i][j - 1] * ps[i];
	}
	for(i = 0; i < n; i++)
		//scanf("%lld", &a[i]);
		a[i] = rand() % 100000;
	for(i = 0; i < n; i++) {
		ll x = a[i];
		for(j = 0; j < ps.size(); j++)
			while(!(x % ps[j]))
				x /= ps[j], ct[i][j]++;
	}
	for(i = 0; i < div.size(); i++) {
		ll x = div[i];
		for(j = 0; j < ps.size(); j++)
			while(!(x % ps[j]))
				x /= ps[j], cd[i][j]++;
	}
	if(solve(0, k).fst > n) { puts("-1"); return 0; }
	build(0, k);
}

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
const ll M = 10004205361450474;

int go(vector<ll> v) {
	printf("%d", int(v.size()));
	printf("(%lld %lld)", v.front(), v.back());
	//for(ll x : v) printf(" %lld", x);
	putchar('\n');
	fflush(stdout);
	int ans;
	scanf("%d", &ans);
	if(ans < 0) exit(0);
	return ans;
}

typedef long double dbl;

void solve(int k, ll l, ll r) {
	printf("k = %d (%lld, %lld) sz %lld\n", k, l, r, r - l + 1ll);
	if(l == 1 && k > 2) {
		ll x = ll(powl(dbl(r), 1. / (k - 1)) + 0.5);
		int ans = go({x});
		if(ans == 0) return solve(k - 1, l, x - 1);
		else return solve(k - 1, x + 1, r);
	} else if(l == 1 && k == 2) {
		int ans = go({2});
		if(ans == 0) go({1});
		else go({3});
	}
	int g = min(10000ll, l);
	vector<ll> v;
	for(int i = 0; i < g; i++) {
		dbl x = dbl(r - l) / dbl(g + 1);
		ll y = ll((x * dbl(i + 1)) + l + 0.5);
		if(!v.empty() && y <= v.back()) y = v.back() + 1;
		v.pb(y);
	}
	int ans = go(v);
	if(ans == 0) return solve(k - 1, l, v[0] - 1);
	if(ans == g) return solve(k - 1, v.back() + 1, r);
	return solve(k - 1, v[ans - 1] + 1, v[ans] - 1);
}

int main() {
	solve(5, 1, M);
}

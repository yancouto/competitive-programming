#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

int p[] = {2, 3, 5, 7};
vector<ll> all;
void brut(int i, ll x) {
	if(i == 4) {
		all.pb(x);
		return;
	}
	while(x <= 1000000000000000000ll) {
		brut(i + 1, x);
		x *= p[i];
	}
}

inline int gi(ll x) { return lower_bound(all.begin(), all.end(), x) - all.begin(); }

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

vector<vector<int>> dvs, to;

int memo[102][70000][2];
bool seen[102][70000][2];
inline ll solve(int i, int pi, bool l0) {
	if(i == 100) return !l0 && all[pi] == 1;
	if(seen[i][pi][l0]) return memo[i][pi][l0];
	seen[i][pi][l0] = 1;
	ll r = 0;
	if(l0) r = solve(i + 1, pi, true); // 0
	for(int T : to[pi])
		r += solve(i + 1, T, false);
	return memo[i][pi][l0] = mod(r);
}

int main() {
	brut(0, 1);
	int t;
	sort(all.begin(), all.end());
	for(ll px : all) {
		dvs.pb(vector<int>());
		to.pb(vector<int>());
		for(int i = 1; i < 10; i++)
			if(!(px % i)) {
				dvs.back().pb(i);
				to.back().pb(gi(px / i));
			}
	}
	int i, j, l0;
	for(i = 99; i >= 0; i--)
		for(j = 0; j < int(all.size()); j++)
			for(l0 = 0; l0 <= 1; l0++)
				solve(i, j, l0);
	scanf("%d", &t);
	while(t--) {
		ll p;
		scanf("%lld", &p);
		ll px = p;
		for(int i = 2; i <= 9; i++)
			while(px && !(px % i))
				px /= i;
		if(p == 0) {
			ll ans = 1;
			ll p9 = 1, p10 = 1;
			for(int i = 1; i <= 100; i++) {
				p9 = mod(p9 * 9ll);
				ans = mod(ans + 9ll * p10 - p9);
				p10 = mod(p10 * 10ll);
			}
			printf("%lld\n", ans);
		} else if(px != 1) {
			puts("0");
		} else {
			printf("%lld\n", solve(0, gi(p), true));
		}
	}
}

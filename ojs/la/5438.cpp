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

int S; ll P;
char s[20];
unordered_map<ll, ll> memo[15][140][2];
ll solve(int i, int sum, ll prod, bool pre) {
	if(sum > S) return 0;
	if(!s[i]) return sum == S && prod == P && !pre;
	auto it = memo[i][sum][pre].find(prod);
	if(it != memo[i][sum][pre].end()) return it->snd;
	ll &r = memo[i][sum][pre][prod];
	for(int d = 0; d <= 9 && sum + d <= S; d++) {
		if(pre && d > s[i] - '0') break;
		if(!(P % (prod * ll(d + 1))))
			r += solve(i + 1, sum + d, prod * ll(d + 1), pre && d == s[i] - '0');
	}
	return r;
}

map<ll, ll> dp[15][130];
ll sa[15][130];

int main() {
	int i, j, sum, d;
	// # of numbers
	dp[0][0][1] = 1;
	for(i = 0; i < 14; i++)
		for(sum = 0; sum < 130; sum++)
			for(auto p : dp[i][sum])
				for(d = 0; d <= 9 && sum + d < 130; d++) {
					dp[i + 1][sum + d][p.fst * ll(d + 1)] += p.snd;
				}
	// acc sums
	for(i = 1; i < 15; i++)
		for(sum = 0; sum < 130; sum++) {
			for(auto p : dp[i][sum])
				sa[i][sum] += p.snd;
			if(sum) sa[i][sum] += sa[i][sum - 1];
		}
	// acc prod
	for(i = 1; i < 15; i++)
		for(sum = 0; sum < 130; sum++) {
			dp[i][sum][-1] = 0;
			for(auto it = next(dp[i][sum].begin()); it != dp[i][sum].end(); ++it)
				it->snd += prev(it)->snd;
		}

	while(scanf("%s", s) != EOF) {
		S = 0; P = 1;
		for(i = 0; s[i]; i++) S += s[i] - '0', P *= (s[i] - '0' + 1);
		ll ans = (S? sa[i][S - 1] : 0);
		ans += prev(dp[i][S].find(P))->snd;
		for(i = 0; s[i]; i++)
			for(j = 0; j <= S; j++)
				for(int k = 0; k < 2; k++)
					memo[i][j][k].clear();
		printf("%lld\n", ans + solve(0, 0, 1, true));
	}
}

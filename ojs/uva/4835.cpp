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

ll memo2[102][102];
ll comb(int n, int p) {
	if(p > n) return 0;
	if(p == 0) return 1;
	if(memo2[n][p] == -1) memo2[n][p] = mod(comb(n - 1, p) + comb(n - 1, p - 1));
	return memo2[n][p];
}

int k;
ll memo[102][102];
ll solve(int n, int d) {
	if(d == k) return !n;
	if(n == 0) return 1;
	ll &r = memo[n][d];
	if(r != -1) return r;
	r = 0;
	for(int s = 1; s <= n; s++)
		r = mod(r + mod(comb(n - 1, s - 1) * s) * mod(solve(s - 1, 1) * solve(n - s, d + 1)));
	return r;
}

int main() {
	int n;
	while(scanf("%d %d", &n, &k) != EOF) {
		memset(memo, -1, sizeof memo);
		memset(memo2, -1, sizeof memo2);
		printf("%d\n", (int) solve(n - 1, 0));
	}
}

#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int memo[22][12][160];
int solve(int n, int k, int s) {
	if(k == 0) return s == 0;
	int &r = memo[n][k][s];
	if(r != -1) return r;
	r = 0;
	for(int i = 1; i <= n && i <= s; i++)
		r += solve(i - 1, k - 1, s - i);
	return r;
}

int main() {
	memset(memo, -1, sizeof memo);
	int n, k, s;
	while(scanf("%d %d %d", &n, &k, &s) != EOF && n)
		printf("%d\n", solve(n, k, s));
}

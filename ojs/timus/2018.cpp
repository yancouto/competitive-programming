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

int a[2];
ll memo[51234][2];
ll solve(int n, int b) {
	if(n == 0) return 1;
	ll &r = memo[n][b];
	if(r != -1) return r;
	r = 0;
	for(int i = 1; i <= a[b] && i <= n; i++)
		r += solve(n - i, !b);
	return r = mod(r);
}

int main() {
	int n;
	scanf("%d %d %d", &n, &a[0], &a[1]);
	memset(memo, -1, sizeof memo);
	printf("%d\n", (int)mod(solve(n, 0) + solve(n, 1)));
}

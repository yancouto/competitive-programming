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

int n, a[1123];
int memo[109][50009];
int solve(int i, int m) {
	if(m < 0) return 1e5;
	if(m == 0) return 0;
	if(i == n) return 1e5;
	int &r = memo[i][m];
	if(r != -1) return r;
	return r = min(solve(i + 1, m), 1 + solve(i, m - a[i]));
}

int main() {
	int i, m;
	while(scanf("%d %d", &m, &n) != EOF && m) {
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		memset(memo, -1, sizeof memo);
		if(solve(0, m) >= 1e5) puts("Impossivel");
		else printf("%d\n", solve(0, m));
	}
}

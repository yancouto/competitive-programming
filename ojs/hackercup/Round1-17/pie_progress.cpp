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

int n, m;
int c[312][312];
int memo[312][312];
int seen[312][312], t;
int solve(int i, int ps) {
	int &r = memo[i][ps];
	if(seen[i][ps] == t) return r;
	seen[i][ps] = t;
	if(i == n) return r = 0;
	r = INT_MAX;
	int cur = 0;
	for(int g = !ps; g <= m; g++) {
		if(g) cur += c[i][g - 1];
		r = min(r, solve(i + 1, min(ps + g - 1, n)) + cur + g * g);
	}
	return r;
}

int main() {
	int i, j;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf("%d", &c[i][j]);
		for(i = 0; i < n; i++) sort(c[i], c[i] + m);
		t++;
		printf("Case #%d: %d\n", tt, solve(0, 0));
	}
}

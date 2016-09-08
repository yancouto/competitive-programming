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

ll memo[103][11][1024][22];
int seen[103][11][1024][22], t;
char a[103][103];
int n, m, c, d;
ll solve(int i, int j, int bm, int ct) {
	if(j == m) return solve(i + 1, 0, bm, ct);
	if(i == n) return bm == 0 && ct >= c;
	ll &r = memo[i][j][bm][ct];
	if(seen[i][j][bm][ct] == t) return r;
	seen[i][j][bm][ct] = t;
	r = 0;
	if(((bm >> j) & 1) || a[i][j] == '0') r += solve(i, j + 1, bm & (~(1 << j)), ct);
	if(!((bm >> j) & 1) && a[i][j] == '1' && ct < d) r += solve(i, j + 1, bm, ct + 1);
	if(!((bm >> j) & 3) && a[i][j] == '1' && j < m - 1 && a[i][j + 1] == '1') r += solve(i, j + 2, bm, ct);
	if(!((bm >> j) & 1) && a[i][j] == '1' && i < n - 1 && a[i + 1][j] == '1') r += solve(i, j + 1, bm | (1 << j), ct);
	return r = mod(r);
}

int main() {
	int i, j;
	while(scanf("%d %d %d %d", &n, &m, &c, &d) != EOF) {
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf(" %c", &a[i][j]);
		t++;
		printf("%d\n", (int) solve(0, 0, 0, 0));
	}
}

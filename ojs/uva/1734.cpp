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
const int N = 112;
int d[N][N];

int main() {
	int i, j, k, n, m, a, b, c;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				d[i][j] = 1e8;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c); a--; b--;
			d[a][b] = min(d[a][b], c);
			d[b][a] = min(d[b][a], c);
		}
		for(i = 0; i < n; i++) d[i][i] = 0;
		for(k = 0; k < n; k++)
			for(i = 0; i < n; i++)
				for(j = 0; j < n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		int ans = INT_MAX;
		for(i = 0; i < n; i++) {
			for(k = 1; k < 5 && d[k][i] == d[k - 1][i]; k++);
			if(k < 5) continue;
			int r = 0;
			for(j = 0; j < n; j++)
				r = max(r, d[i][j]);
			if(r < 100000000) ans = min(ans, r);
		}
		printf("Map %d: ", tt);
		if(ans == INT_MAX) puts("-1");
		else printf("%d\n", ans);
	}
}

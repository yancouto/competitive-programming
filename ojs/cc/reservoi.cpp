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

int di[] = {1,  0, 0};
int dj[] = {0, -1, 1};
char g[1123][1123];

int main() {
	int i, j, n, m, d;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 1; i <= n; i++) scanf("%s", g[i] + 1);
		bool ok = true;
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++) {
				if(g[i][j] == 'B' && g[i + 1][j] == 'A') ok = false;
				for(d = 0; d < 3; d++) {
					int ni = i + di[d], nj = j + dj[d];
					if(g[i][j] == 'W' && g[ni][nj] != 'W' && g[ni][nj] != 'B')
						ok = false;
				}
			}
		if(ok) puts("yes");
		else puts("no");
	}
}

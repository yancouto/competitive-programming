#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

int g[1003][1003];
int d1[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
int d2[8][2] = {{2, 1}, {-2, 1}, {2, -1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

int main() {
	int i, j, d, n, m, k, p, x, y, t = 0;
	int ri[200], rj[200];
	while(true) {
		scanf("%d %d", &n, &m);
		if(!n && !m) return 0;
		scanf("%d", &k);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				g[i][j] = 0;
		for(i = 0; i < k; i++) {
			scanf("%d %d", &ri[i], &rj[i]);
			g[--ri[i]][--rj[i]] = 1;
		}
		scanf("%d", &p);
		for(i = 0; i < p; i++) {
			scanf("%d %d", &x, &y);
			g[--x][--y] = 1;
			for(j = 0; j < 8; j++) {
				int ni = x + d2[j][0], nj = y + d2[j][1];
				if(ni < 0 || ni >= n || nj < 0 || nj >= m || g[ni][nj] == 1) continue;
				g[ni][nj] = 2;
			}
		}
		scanf("%d", &p);
		for(i = 0; i < p; i++) {
			scanf("%d %d", &x, &y);
			g[--x][--y] = 1;
		}
		for(i = 0; i < k; i++)
			for(d = 0; d < 8; d++)
				for(j = 1; ; j++) {
					int ni = ri[i] + j*d1[d][0], nj = rj[i] + j*d1[d][1];
					if(ni < 0 || ni >= n || nj < 0 || nj >= m || g[ni][nj] == 1) break;
					g[ni][nj] = 2;
				}
		int ct = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				ct += !g[i][j];
		printf("Board %d has %d safe squares.\n", ++t, ct);
	}
}

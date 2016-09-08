#include <bits/stdc++.h>
using namespace std;
#define i first
#define j second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 110;

int a[N][N], mn[N][N], seen[N][N];
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, -1, 1};

int main() {
	int i, j, n, sx, sy, ex, ey;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 1; i <= n; i++)
			for(j = 1; j <= n; j++)
				scanf("%d", &a[i][j]), mn[i][j] = 100, seen[i][j] = 0;
		scanf("%d %d", &sx, &sy); sx++; sy++;
		for(i = 1; i < (1 << 10); i++) {
			queue<pii> q;
			if(!((1 << a[sx][sy]) & i)) continue;
			q.push(pii(sx, sy));
			while(!q.empty()) {
				pii x = q.front(); q.pop();
				mn[x.i][x.j] = min(mn[x.i][x.j], __builtin_popcount(i));
				for(int d = 0; d < 4; d++) {
					pii y(x.i + di[d], x.j + dj[d]);
					if(y.i <= 0 || y.j <= 0 || y.i > n || y.j > n || !((1 << a[y.i][y.j]) & i) || seen[y.i][y.j] == i) continue;
					seen[y.i][y.j] = i;
					q.push(y);
				}
			}
		}
		scanf("%d %d", &ex, &ey); ex++; ey++;
		printf("%d\n", mn[ex][ey]);
	}
}

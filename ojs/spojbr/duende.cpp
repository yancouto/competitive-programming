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

int g[100][100], d[100][100];
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, -1, 1};
int n, m;
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }

int main() {
	queue<pii> q;
	int i, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			d[i][j] = INT_MAX;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			scanf("%d", &g[i][j]);
			if(g[i][j] == 3) {
				d[i][j] = 0;
				q.push(pii(i, j));
			}
		}
	while(!q.empty()) {
		pii x = q.front(); q.pop();
		if(g[x.i][x.j] == 0) { printf("%d\n", d[x.i][x.j]); return 0; }
		for(int d = 0; d < 4; d++) {
			int ni = x.i + di[d], nj = x.j + dj[d];
			if(valid(ni, nj) && g[ni][nj] != 2 && ::d[ni][nj] == INT_MAX) {
				::d[ni][nj] = ::d[x.i][x.j] + 1;
				q.push(pii(ni, nj));
			}
		}
	}
}

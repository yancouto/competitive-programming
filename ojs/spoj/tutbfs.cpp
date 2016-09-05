#include <bits/stdc++.h>
using namespace std;
#define i first
#define j second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 100;
char g[N][N];
int d[N][N];
int n, m;
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m && g[i][j] == '.'; }

int di[8] = {1, -1, 0, 0, 1, 1, -1, -1};
int dj[8] = {0, 0, -1, 1, 1, -1, 1, -1};

int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf(" %c", &g[i][j]), d[i][j] = -1;
		queue<pii> q;
		q.push(pii(0, 0)); d[0][0] = 0;
		int ans;
		while(!q.empty()) {
			pii x = q.front(); q.pop();
			ans = d[x.i][x.j];
			for(int dd = 0; dd < 8; dd++) {
				int ni = x.i + di[dd], nj = x.j + dj[dd];
				if(!valid(ni, nj) || d[ni][nj] != -1) continue;
				d[ni][nj] = d[x.i][x.j] + 1;
				q.push(pii(ni, nj));
			}
		}
		printf("%d\n", ans);
	}
}

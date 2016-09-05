#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int di[8] = {1, -1, 0, 0, 1, 1, -1, -1};
int dj[8] = {0, 0, -1, 1, 1, -1, 1, -1};
int n, m, mx;
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }
int seen[60][60];
char g[60][60];
void dfs(int i, int j) {
	seen[i][j] = true;
	mx = max(mx, g[i][j] - 'A' + 1);
	for(int d = 0; d < 8; d++) {
		int ni = i + di[d], nj = j + dj[d];
		if(!valid(ni, nj) || g[ni][nj] != g[i][j] + 1 || seen[ni][nj]) continue;
		dfs(ni, nj);
	}
}

int main() {
	int i, j, t = 0;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf(" %c", &g[i][j]), seen[i][j] = false;
		mx = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				if(g[i][j] == 'A')
					dfs(i, j);
		printf("Case %d: %d\n", ++t, mx);
	}
}

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

char g[1009][1009];
int c[1009][1009];
int num[1002 * 1002];
int tempo;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int dfs(int i, int j) {
	c[i][j] = tempo;
	num[tempo]++;
	for(int d = 0; d < 4; d++) {
		int ni = i + dx[d], nj = j + dy[d];
		if(g[ni][nj] == 'n' && !c[ni][nj])
			dfs(ni, nj);
	}
}

int count(int i, int j) {
	set<int> s;
	for(int d = 0; d < 4; d++) {
		int ni = i + dx[d], nj = j + dy[d];
		if(g[ni][nj] == 'n') s.insert(c[ni][nj]);
	}
	int tot = 0;
	for(int x : s)
		tot += num[x];
	return tot;
}

int main() {
	int i, j, n, m;
	scanf("%d %d", &n, &m);
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++)
			scanf(" %c", &g[i][j]);
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++)
			if(!c[i][j] && g[i][j] == 'n') {
				tempo++;
				dfs(i, j);
			}
	int mi = -1, mj = -1, md = 0;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++)
			if(g[i][j] == '*' && (mi == -1 || count(i, j) > md))
				mi = i, mj = j, md = count(i, j);
	printf("%d,%d\n", mi, mj);
}

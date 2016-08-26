// TLE
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

char g[2009][2009];
int seen[2009][2009], li, lj, ri, rj, n, m, t;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }
void dfs(int i, int j) {
	li = min(li, i);
	ri = max(ri, i);
	lj = min(lj, j);
	rj = max(rj, j);
	if(s2[i][j] == t) return;
	seen[i][j] = 1;
	s2[i][j] = t;
	g[i][j] = '.';
	for(int d = 0; d < 4; d++) {
		int ni = i + dx[d], nj = j + dy[d];
		if(!valid(ni, nj)) continue;
		if(ni >= li && ni <= ri && nj >= lj && nj <= rj)
			dfs(ni, nj);
		else if(g[ni][nj] == '.') dfs(ni, nj);
	}
}

int main() {
	int i, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf(" %c", &g[i][j]);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(seen[i][j] <= t && g[i][j] == '.') {
				li = ri = i;
				lj = rj = j; t++;
				dfs(i, j);
			}
	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++)
			putchar(g[i][j]);
		putchar('\n');
	}
}

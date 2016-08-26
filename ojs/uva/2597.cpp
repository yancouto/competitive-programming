#include <bits/stdc++.h>
using namespace std;
#define i first
#define j second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int dx[4] = {1, -1, 0,  0};
int dy[4] = {0,  0, 1, -1};
int seen[53][53], tempo;
char g[53][53];

bool near_trap(int i, int j) {
	for(int d = 0; d < 4; d++)
		if(g[i + dx[d]][j + dy[d]] == 'T')
			return true;
	return false;
}

int main() {
	int i, j, w, h; pii si;
	while(scanf("%d %d", &w, &h) != EOF) {
		for(i = 0; i < h; i++)
			for(j = 0; j < w; j++) {
				scanf(" %c", &g[i][j]);
				if(g[i][j] == 'P')
					si = pii(i, j);
			}
		queue<pii> q;
		q.push(si); tempo++;
		int tot = 0;
		while(!q.empty()) {
			pii n = q.front(); q.pop();
			if(g[n.i][n.j] == 'G') tot++;
			if(near_trap(n.i, n.j)) continue;
			for(i = 0; i < 4; i++) {
				int ni = n.i + dx[i], nj = n.j + dy[i];
				if(g[ni][nj] != '#' && seen[ni][nj] < tempo) {
					seen[ni][nj] = tempo;
					q.push(pii(ni, nj));
				}
			}
		}
		printf("%d\n", tot);
	}
}

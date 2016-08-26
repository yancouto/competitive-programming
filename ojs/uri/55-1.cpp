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
char grid[102][102];

struct no {
	int i, j, bm;
	no() {}
	no(int a, int b, int c) : i(a), j(b), bm(c) {}
};

int dist[102][102][130];
int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool valid(int i, int j) { return i >= 0 && j >= 0 && grid[i][j]; }
int bfs(int si, int sj) {
	memset(dist, -1, sizeof dist);
	queue<no> q;
	dist[si][sj][0] = 0;
	q.push(no(si, sj, 0));
	grid[si][sj] = '.';
	while(!q.empty()) {
		no x = q.front();
		q.pop();
		for(int i = 0; i < 4; i++) {
			int ni = x.i + d[i][0], nj = x.j + d[i][1], bm = x.bm;
			if(!valid(ni, nj)) continue;
			char c = grid[ni][nj];
			if(c == '*') return dist[x.i][x.j][x.bm] + 1;
			if(c == '#') continue;
			else if(c >= 'A' && c <= 'G') {
				if(!(x.bm & (1 << (c - 'A'))))
					continue;
			}
			else if(c >= 'a' && c <= 'g')
				bm |= (1 << (c - 'a'));
			else if(c != '.') continue;
			if(dist[ni][nj][bm] == -1) {
				dist[ni][nj][bm] = dist[x.i][x.j][x.bm] + 1;
				q.push(no(ni, nj, bm));
			}
		}
	}
	return -1;
}

int main() {
	int i, n = 0;
	while(scanf(" %s", grid[n]) != EOF) n++;
	for(i = 0; i < n; i++) {
		char *c = strchr(grid[i], '@');
		if(c) {
			int a = bfs(i, c - grid[i]);
			if(a != -1) printf("%d\n", a);
			else puts("--");
			return 0;
		}
	}
}

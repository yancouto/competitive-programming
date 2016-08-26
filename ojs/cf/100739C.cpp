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
int n;
char g[203][203];
int dist[203][203][4];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
struct no {
	int i, j, d;
};
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && g[i][j]; }
int bfs() {
	memset(dist, -1, sizeof dist);
	dist[0][0][0] = 0;
	queue<no> q;
	q.push({0, 0, 0});
	while(!q.empty()) {
		no x = q.front(); q.pop();
		if(x.i == n - 1 && x.j == n - 1 && x.d == 0) return dist[x.i][x.j][x.d];
		int ni = x.i + dx[x.d], nj = x.j + dy[x.d];
		if(valid(ni, nj) && g[ni][nj] == '.' && dist[ni][nj][x.d] == -1) {
			dist[ni][nj][x.d] = dist[x.i][x.j][x.d] + 1;
			q.push(no{ni, nj, x.d});
		}
		if(dist[x.i][x.j][(x.d + 1)%4] == -1) {
			dist[x.i][x.j][(x.d + 1)%4] = dist[x.i][x.j][x.d] + 1;
			q.push(no{x.i, x.j, (x.d+1)%4});
		}
	}
	return -1;
}

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf(" %c", &g[i][j]);
	printf("%d\n", bfs());
}

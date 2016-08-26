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
int n;

pii q[10009];
int dist[102][102];
int di[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < n; }
int bfs(int bm) {
	char c = grid[0][0];
	if(isupper(c) && !(bm & (1 << (c - 'A')))) return INT_MAX;
	if(islower(c) &&  (bm & (1 << (c - 'a')))) return INT_MAX;
	int a = 0, b = 0;
	q[b++] = pii(0, 0);
	memset(dist, -1, sizeof dist);
	dist[0][0] = 0;
	while(a < b) {
		pii x = q[a++];
		if(x.fst == n - 1 && x.snd == n - 1)
			return dist[x.fst][x.snd];
		for(int i = 0; i < 4; i++) {
			int ni = x.fst + di[i][0], nj = x.snd + di[i][1];
			if(!valid(ni, nj)) continue;
			c = grid[ni][nj];
			if(isupper(c) && !(bm & (1 << (c - 'A')))) continue;
			if(islower(c) &&  (bm & (1 << (c - 'a')))) continue;
			if(dist[ni][nj] != -1) continue;
			dist[ni][nj] = dist[x.fst][x.snd] + 1;
			q[b++] = pii(ni, nj);
		}
	}
	return INT_MAX;
}

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf(" %s", grid[i]);
	int mn = INT_MAX;
	for(i = 0; i < 1024; i++)
		mn = min(bfs(i), mn);
	if(mn == INT_MAX) puts("-1");
	else printf("%d\n", mn+1);
}

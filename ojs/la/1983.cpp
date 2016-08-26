// WA ???
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

map<string, int> adj[2][1009];
int m[2], n[2], pr[2];
char str[100];
int dist[1009][1009];
int bfs() {
	memset(dist, -1, sizeof dist);
	queue<pii> q;
	q.push(pii(0, 0));
	dist[0][0] = 0;
	while(!q.empty()) {
		pii x = q.front(); q.pop();
		if(x.fst == pr[0] && x.snd == pr[1]) return dist[x.fst][x.snd];
		for(auto &it : adj[0][x.fst]) {
			if(!adj[1][x.snd].count(it.fst)) continue;
			int a = it.snd, b = adj[1][x.snd][it.fst];
			if(dist[a][b] != -1) continue;
			dist[a][b] = dist[x.fst][x.snd] + 1;
			q.push(pii(a, b));
		}
	}
	return -1;
}


int main() {
	int i, j, a, b;
	for_tests(t, tt) {
		if(tt > 1) putchar('\n');
		for(i = 0; i < 2; i++) {
			scanf("%d %d %d", &n[i], &pr[i], &m[i]);
			for(j = 0; j < m[i]; j++) {
				scanf("%d %s %d", &a, str, &b);
				string s(str);
				adj[i][a][s] = b;
				adj[i][b][s] = a;
			}
		}
		printf("%d\n", bfs());
		for(i = 0; i < max(n[0], n[1]); i++) { adj[0][i].clear(); adj[1][i].clear(); }
	}
	return 0;
}

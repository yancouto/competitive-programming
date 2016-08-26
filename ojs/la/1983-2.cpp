// WAA??
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

const int MAX = 1009;
int l[2], pr[2], p[2];
map<int, int> adj[2][MAX];

map<string, int> mp;
int get(string s) {
	if(!mp.count(s)) mp[s] = mp.size() - 1;
	return mp[s];
}

int dist[MAX][MAX];
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

char str[100];
int main() {
	int i, j, a, b;
	for_tests(t, tt) {
		if(tt > 1) putchar('\n');
		for(i = 0; i < 2; i++) {
			scanf("%d %d %d", &l[i], &pr[i], &p[i]);
			for(j = 0; j < l[i]; j++) adj[i][j].clear();
			for(j = 0; j < p[i]; j++) {
				scanf("%d %s %d", &a, str, &b);
				int ind = get(str);
				adj[i][a][ind] = b;
				adj[i][b][ind] = a;
			}
		}
		printf("%d\n", bfs());
	}
	return 0;
}

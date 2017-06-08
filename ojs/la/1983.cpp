#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int n[2], p[2], m[2];
multimap<string, int> adj[2][1123]; // multiple edges with same name
int d[1123][1123];

char s[1123];
int main() {
	int i, j, a, b;
	for_tests(tn, tt) {
		if(tt > 1) putchar('\n');
		for(j = 0; j < 2; j++) {
			scanf("%d %d %d", &n[j], &p[j], &m[j]);
			for(i = 0; i < n[j]; i++) adj[j][i].clear();
			for(i = 0; i < m[j]; i++) {
				scanf("%d %s %d", &a, s, &b);
				adj[j][a].insert(pair<string, int>(s, b));
			}
		}
		for(i = 0; i < n[0]; i++)
			for(j = 0; j < n[1]; j++)
				d[i][j] = -1;
		queue<pii> q;
		q.push(pii(0, 0));
		d[0][0] = 0;
		int ans = -1;
		while(!q.empty()) {
			pii x = q.front(); q.pop();
			if(x.fst == p[0] && x.snd == p[1]) {
				ans = d[x.fst][x.snd];
				break;
			}
			for(auto sa : adj[0][x.fst]) {
				auto sb = adj[1][x.snd].lower_bound(sa.fst);
				for(; sb != adj[1][x.snd].end() && sb->fst == sa.fst; ++sb) {
					a = sa.snd;
					b = sb->snd;
					if(d[a][b] == -1) {
						d[a][b] = d[x.fst][x.snd] + 1;
						q.push(pii(a, b));
					}
				}
			}
		}
		printf("%d\n", ans);
	}
}

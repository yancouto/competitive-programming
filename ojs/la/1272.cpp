#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
#define pb push_back

pii operator + (pii a, pii b) { return pii(a.fst + b.fst, a.snd + b.snd); }
int all, n, to;
vector<pii> adj[23];

pii memo[1100009];
pii solve(int bm) {
	if((bm | all) == bm) return pii(0, 0);
	pii &r = memo[bm];
	if(r.fst != -1) return r;
	r = pii(1000000000, 1000000000);
	for(int i = 0; i < n; i++)
		if(bm & (1 << i))
			for(pii e : adj[i])
				if(!(bm & (1 << e.fst)))
					r = min(r, pii(e.snd, 1) + solve(bm | (1 << e.fst)));
	return r;
}

int p[29];
void build(int bm) {
	if((bm | all) == bm) return;
	for(int i = 0; i < n; i++)
		if(bm & (1 << i))
			for(pii e : adj[i])
				if(!(bm & (1 << e.fst)) && solve(bm) == pii(e.snd, 1) + solve(bm | (1 << e.fst))) {
					p[e.fst] = i;
					build(bm | (1 << e.fst));
					return;
				}
}


int main() {
	int i, m, a, b, c, t = 0;
	while(scanf("%d %d %d", &n, &to, &m) != EOF) {
		if(n == -1) return 0;
		to--;
		for(i = 0; i < n; i++)
			adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c); a--; b--;
			adj[a].pb(pii(b, c));
			adj[b].pb(pii(a, c));
		}
		for(i = 0; i < n; i++)
			sort(adj[i].begin(), adj[i].end());
		scanf("%d", &b);
		all = 0;
		int g[22];
		for(i = 0; i < b; i++) {
			scanf("%d", &g[i]);
			all |= (1 << (--g[i]));
		}
		memset(memo, -1, sizeof memo);
		printf("Case %d: distance = %d\n", ++t, solve(1 << to).fst);
		build(1 << to);
		for(i = 0; i < b; i++) {
			printf("   ");
			a = g[i];
			while(a != to) {
				printf("%d-", a + 1);
				a = p[a];
			}
			printf("%d\n", to + 1);
		}
		putchar('\n');
	}
}

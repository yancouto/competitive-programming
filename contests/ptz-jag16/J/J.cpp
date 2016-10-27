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

void dij(int g, vector<int> *adj, int s) {
	priority_queue<pii> pq;
	pq.push(pii(0, s));
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(seen[g][x.snd]) continue;
		seen[g][x.snd] = 1;
		d[g][x.snd] = -x.fst;
		for(pii e : adj[x.snd])
			pq.push(pii(x.fst - e.snd, e.fst));
	}
}

int main() {
	scanf("%d %d %d %d %d", &n, &m, &p, &s, &t); s--; t--;
	for(i = 0; i < m; i++) {
		scanf("%d %d %d %d", &a[i], &b[i], &l[i], &c[i]); a[i]--; b[i]--;
		adj[a[i]].pb(pii(b[i], l[i]));
		rev[b[i]].pb(pii(a[i], l[i]));
	}
	dij(0, adj, s);
	dij(1, rev, t);
	int dist = d[0][t];
	vector<int> ed;
	for(i = 0; i < m; i++)
		if(dist == d[0][a[i]] + l[i] + d[1][b[i]])
			add_edge(a[i], b[i], c[i]);
		else ed.pb(i);
	while(true) {
		max_flow(s, t);
		int x = cur_flow;
		vector<int> v;
		int mn = INT_MAX;
		for(int i : ed)
			if(!us[i] && seen[a[i]] == tempo && seen[b[i]] < tempo) {
				v.pb(i);
				mn = min(mn, d[0][a[i]] + l[i] + d[1][b[i]] - dist);
			}
		if(v.empty() || p / x < mn) {
			printf("%.10f\n", dist + double(p) / x);
			return 0;
		} else {
			p -= x * mn;
			assert(p >= 0);
			for(int i : v)
				if(d[0][a[i]] + l[i] + d[1][b[i]] - dist == mn) {
					add_edge(a[i], b[i], c[i]);
					us[i] = 1;
				}
		}
	}
}

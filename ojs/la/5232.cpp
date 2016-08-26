#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

struct no {
	pii p;
	int d, mx;
	bool operator < (no o) const { return d > o.d; }
};

int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};
int mrk1[103][103][10], t, n, m;
inline int& mrk(no x) { return mrk1[x.p.fst][x.p.snd][x.mx]; }
char g[103][103];
inline char G(pii p) { return g[p.fst][p.snd]; }
inline bool valid(pii p) { return p.fst >= 0 && p.snd >= 0 && p.fst < n && p.snd < m; }
int dist[103][103][10];

int solve(pii st, pii en) {
	t++;
	priority_queue<no> pq;
	pq.push({st, 0, 0});
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(mrk(x) == t) continue;
		mrk(x) = t;
		dist[x.p.fst][x.p.snd][x.mx] = x.d;
		for(int d = 0; d < 4; d++) {
			pii n(x.p.fst + di[d], x.p.snd + dj[d]);
			if(!valid(n) || !isdigit(G(n))) continue;
			pq.push({n, x.d + G(n) - '0', max(x.mx, G(n) - '0')});
		}
	}
}

int main() {
	int i, j;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		int tot = 0; pii st, en;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				scanf(" %c", &g[i][j]);
				if(isdigit(g[i][j])) tot += g[i][j] - '0';
				if(g[i][j] == '0') g[i][j] = '*';
				if(g[i][j] == 'A') g[i][j] = '0', st = pii(i, j);
				if(g[i][j] == 'B') g[i][j] = '0', en = pii(i, j);
			}
		int mn = tot;
		solve(st, en);
		for(i = 1; i <= 9; i++)
			if(mrk({en, 0, i}) == t)
				mn = min(mn, dist[en.fst][en.snd][i] - i);
		printf("Case #%d: %d\n", tt, tot - mn);
	}
}

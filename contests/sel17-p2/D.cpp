#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1123;
int n, t;
int d[N][N];
int ps[N], pn;

struct st {
	int i;
	int from;
	int f() {
		if(from == n) return 0;
		return t - ::d[from][i];
	}
	ll d;
	bool operator < (const st &o) const { return d > o.d; }
};


const int inf = INT_MAX;

int p[N];
int seen[129][129];
int dist[129][129];
int mp[N];

bool is[N];

#define fst first
#define snd second
typedef pair<int, int> pii;
#define pb push_back
vector<pii> adj[N];

void go(int i) {
	typedef pair<ll, int> pli;
	priority_queue<pli> pq;
	pq.push(pli(0, i));
	for(int j = 0; j < n; j++) d[i][j] = inf;
	while(!pq.empty()) {
		pli x = pq.top(); pq.pop();
		if(d[i][x.snd] != inf) continue;
		d[i][x.snd] = -x.fst;
		for(pii e : adj[x.snd])
			pq.push(pli(x.fst - e.snd, e.fst));
	}
}

int main() {
	int T;
	scanf("%d", &T); T++;
	int m, s, i, j, k;
	while(--T >= 1) {
		scanf("%d %d %d %d", &n, &m, &s, &t);
		for(i = 0; i < n; i++) is[i] = 0;
		for(i = 0; i < n; i++) adj[i].clear();
		for(i = 0; i < m; i++) {
			int a, b, f;
			scanf("%d %d %d", &a, &b, &f); a--; b--;
			adj[a].pb(pii(b, f));
			adj[b].pb(pii(a, f));
		}

		pn = 0;
		for(i = 0; i < s; i++) {
			int x;
			scanf("%d", &x); x--;
			is[x] = 1;
			scanf("%d", &p[x]);
			mp[x] = pn;
			ps[pn++] = x;
		}
		int C, D;
		scanf("%d %d", &C, &D); C--; D--;
		if(!is[D]) {
			is[D] = 1;
			mp[D] = pn;
			ps[pn++] = D;
		}

		for(i = 0; i < pn; i++)
			go(ps[i]);

		mp[n] = pn;
		priority_queue<st> pq;
		pq.push({C, n, 0});
		while(!pq.empty()) {
			st x = pq.top(); pq.pop();
			if(seen[mp[x.i]][mp[x.from]] == T) continue;
			seen[mp[x.i]][mp[x.from]] = T;
			//printf("(%d, %d) with %lld moniz\n", x.i, x.f, x.d);
			if(x.i == D) {
				printf("%lld\n", x.d);
				break;
			}
			for(i = 0; i < pn; i++) {
				j = ps[i];
				int c = d[x.i][j];
				if(c > t) continue;
				if(seen[mp[j]][mp[x.i]] != T)
					pq.push({j, x.i, x.d + ll(t - x.f()) * ll(p[x.i])});
				if(c < x.f() || seen[mp[j]][mp[n]] == T) continue;
				pq.push({j, n, x.d + ll(c - x.f()) * ll(p[x.i])});
			}
		}
	}
}

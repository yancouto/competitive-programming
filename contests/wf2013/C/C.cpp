#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 31234;
const int M = 112345 * 2;
typedef ll num;
const num eps = 0;

struct dinic {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M];
	num fl[M], cp[M];
	int en = 2;
	int tempo = 0;

	void reset (int n = N) { en = 2; memset(hd, 0, sizeof(int) * n); }
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }

	void add_edge (int a, int b, num c, num rc = 0) {
		to[en] = b; nx[en] = hd[a]; fl[en] = 0; cp[en] = c; hd[a] = en++;
		to[en] = a; nx[en] = hd[b]; fl[en] = 0; cp[en] = rc; hd[b] = en++;
	}

	bool bfs (int s, int t) {
		seen[t] = ++tempo;
		lv[t] = 0;
		int ql = 0, qr = 0;
		qu[qr++] = t;
		while (ql != qr) {
			t = qu[ql++];
			ei[t] = hd[t];
			if (s == t) return true;
			for (int e = hd[t]; e; e = nx[e])
				if (seen[to[e]] != tempo && cp[e^1] - fl[e^1] > eps) {
					seen[to[e]] = tempo;
					lv[to[e]] = lv[t] + 1;
					qu[qr++] = to[e];
				}
		}
		return false;
	}

	num dfs (int s, int t, num f) {
		if (s == t) return f;
		for (int & e = ei[s]; e; e = nx[e])
			if (ei[to[e]] && seen[to[e]] == tempo && cp[e] - fl[e] > eps && lv[to[e]] == lv[s] - 1)
				if (num rf = dfs(to[e], t, min(f, cp[e] - fl[e]))) {
					fl[e] += rf;
					fl[e^1] -= rf;
					return rf;
				}
		return 0;
	}

	num max_flow (int s, int t) {
		num fl = 0;
		while (bfs(s,t))
			while (num f = dfs(s,t,numeric_limits<num>::max()))
				fl += f;
		return fl;
	}
};

dinic di;
int n, m, c;
#define fst first
#define snd second
int d[N];
int p[N];
vector<pii> adj[N];

int main() {
	int i, j, n, m, c;
	scanf("%d %d %d", &n, &m, &c);
	for(i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c); a--; b--;
		adj[a].pb(pii(b, c));
		adj[b].pb(pii(a, c));
	}
	for(i = 0; i < c; i++) {
		scanf("%d", &p[i]);
		p[i]--;
	}
	priority_queue<pii> pq;
	pq.push(pii(0, 0));
	memset(d, -1, sizeof d);
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(d[x.snd] != -1) continue;
		d[x.snd] = -x.fst;
		for(pii e : adj[x.snd])
			pq.push(pii(x.fst - e.snd, e.fst));
	}
	for(i = 0; i < n; i++)
		for(pii e : adj[i])
			if(d[e.fst] == d[i] - e.snd)
				di.add_edge(i, e.fst, 1);
	sort(p, p + c, [](int i, int j) { return d[i] < d[j]; });
	int tot = 0;
	int s = n;
	for(i = 0; i < c; ) {
		j = i;
		while(j + 1 < c && d[p[j + 1]] == d[p[i]]) j++;
		di.reset_flow();
		for(int e = di.hd[s]; e; e = di.nx[e])
			di.cp[e] = 0;
		di.hd[s] = 0;
		for(; i <= j; i++)
			di.add_edge(s, p[i], 1);
		tot += di.max_flow(s, 0);
	}
	printf("%d\n", tot);
}

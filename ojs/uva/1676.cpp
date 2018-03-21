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

typedef int num;
const int N = 1000;
const int M = 2123 * 2;
const num eps = 0;

struct dinic {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M];
	num fl[M], cp[M];
	int en = 2;
	int tempo = 0;

	// Reset the whole graph
	void reset(int n=N) { en = 2; memset(hd, 0, sizeof(int) * n); }
	// Reset only the flow
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }

	// edge from a to b with cap c and edge from b to a with cap rc
	void add_edge(int a, int b, num c, num rc=0) {
		to[en] = b; nx[en] = hd[a]; fl[en] = 0; cp[en] = c; hd[a] = en++;
		to[en] = a; nx[en] = hd[b]; fl[en] = 0; cp[en] = rc; hd[b] = en++;
	}

	bool bfs(int s, int t) {
		seen[t] = ++tempo;
		lv[t] = 0;
		int ql = 0, qr = 0;
		qu[qr++] = t;
		while(ql != qr) {
			t = qu[ql++];
			ei[t] = hd[t];
			if(s == t) return true;
			for(int e = hd[t]; e; e = nx[e])
				if(seen[to[e]] != tempo && cp[e ^ 1] - fl[e ^ 1] > eps) {
					seen[to[e]] = tempo;
					lv[to[e]] = lv[t] + 1;
					qu[qr++] = to[e];
				}
		}
		return false;
	}

	num dfs(int s, int t, num f) {
		if(s == t) return f;
		for(int &e = ei[s]; e; e = nx[e])
			if(ei[to[e]] && seen[to[e]] == tempo && cp[e] - fl[e] > eps && lv[to[e]] == lv[s] - 1)
				if(num rf = dfs(to[e], t, min(f, cp[e] - fl[e]))) {
					fl[e] += rf;
					fl[e ^ 1] -= rf;
					return rf;
				}
		return 0;
	}

	num max_flow(int s, int t) {
		num fl = 0;
		while(bfs(s, t))
			while(num f = dfs(s, t, numeric_limits<num>::max()))
				fl += f;
		return fl;
	}
};

dinic d;

int din[N], dout[N], und[N];
vector<int> adj[N];

int nx[N], val[N], en;

int go(int u) {
	int i = en++;
	nx[i] = 0; val[i] = u;
	while(!adj[u].empty()) {
		int v = adj[u].back(); adj[u].pop_back();
		int j = go(v);
		for(int k = j; ; k = nx[k])
			if(nx[k] == 0) {
				nx[k] = nx[i];
				break;
			}
		nx[i] = j;
	}
	return i;
}

int main() {
	int i, n, m;
	bool fst = true;
	for_tests(tn, tt) {
		if(fst) fst = false;
		else putchar('\n');
		scanf("%d %d", &n, &m);
		d.reset(n + m + 2);
		for(i = 0; i < n; i++) din[i] = 0, dout[i] = 0, und[i] = 0, adj[i].clear();
		vector<pii> eds;
		for(i = 0; i < m; i++) {
			int a, b; char t;
			scanf("%d %d %c", &a, &b, &t); a--; b--;
			if(t == 'U') {
				eds.pb(pii(a, b));
				und[a]++; und[b]++;
			} else {
				din[b]++; dout[a]++;
				adj[a].pb(b);
			}
		}
		int s = n + m, t = n + m + 1;
		for(i = 0; i < eds.size(); i++) {
			d.add_edge(s, i, 1);
			d.add_edge(i, m + eds[i].fst, 1);
			d.add_edge(i, m + eds[i].snd, 1);
		}
		bool bad = false;
		int sum = 0;
		for(i = 0; i < n; i++) {
			int k = (dout[i] + und[i] - din[i]) / 2;
			sum += k;
			if(k < 0 || din[i] + k != dout[i] + und[i] - k) bad = true;
			else d.add_edge(m + i, t, k);
		}
		if(bad || d.max_flow(s, t) != sum) puts("No euler circuit exist");
		else {
			for(i = 0; i < eds.size(); i++) {
				int b;
				for(int e = d.hd[i]; e; e = d.nx[e])
					if(d.fl[e] == 1)
						b = d.to[e] - m;
				adj[eds[i].fst + eds[i].snd - b].pb(b);
			}
			en = 1;
			vector<int> path;
			for(int u = go(0); u; u = nx[u]) path.pb(val[u]);
			for(int i = 0; i < int(path.size()) - 1; i++)
				printf("%d ", path[i] + 1);
			printf("%d\n", path.back() + 1);
		}
	}
}

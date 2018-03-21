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


inline int vin(int u) { return 2 * u; }
inline int vout(int u) { return 2 * u + 1; }

typedef int num;
const int N = 11234;
const int M = 31234567 * 2;
const num eps = 0;

struct dinic {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M];
	num fl[M], cp[M];
	int en;
	int tempo;

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

	void go(int u) {
		if(u == vin(1)) {
			puts("2");
			return;
		}
		if((u % 2) == 1) printf("%d ", (u + 1) / 2);
		for(int e = hd[u]; e; e = nx[e])
			if(fl[e] > 0) {
				fl[e]--;
				return go(to[e]);
			}
	}
};


inline bool rd(int &x) {
	char c;
	while(isspace(c = getchar())) if(c == '\n') return false;
	x = (c - '0');
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + (c - '0');
	ungetc(c, stdin);
	return true;
}

dinic d;

int main() {
	int i, n, k, j; int tt = 0;
	while(scanf("%d %d", &k, &n) != EOF && n) {
		d.reset(2 * n);
		while(getchar() != '\n');
		for(i = 0; i < n; i++) {
			//printf("(%d)\n", i);
			d.add_edge(vin(i), vout(i), 1);
			while(rd(j)) {
				d.add_edge(vout(i), vin(j - 1), 1);
				//printf("%d->%d\n", i + 1, j);
			}
		}
		printf("Case %d:\n", ++tt);
		if(d.max_flow(vout(0), vin(1)) >= k) {
			while(k--)
				d.go(vout(0));
		} else puts("Impossible");
		putchar('\n');
	}
}

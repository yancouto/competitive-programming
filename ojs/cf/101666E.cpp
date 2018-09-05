#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

typedef int num; const int N = 505; const int M = 500 * 500 * 2; const num eps = 0;
struct dinic {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M]; num fl[M], cp[M]; int en = 2; int tempo = 0;
	bool bfs(int s, int t) {
		seen[t] = ++tempo; lv[t] = 0; int ql = 0, qr = 0; qu[qr++] = t;
		while(ql != qr) {
			t = qu[ql++]; ei[t] = hd[t]; if(s == t) return true;
			for(int e = hd[t]; e; e = nx[e]) if(seen[to[e]] != tempo && cp[e ^ 1] - fl[e ^ 1] > eps) {
				seen[to[e]] = tempo;
				lv[to[e]] = lv[t] + 1;
				qu[qr++] = to[e];
			}
		}
		return false;
	}
	num dfs(int s, int t, num f) {
		if(s == t) return f;
		for(int &e = ei[s]; e; e = nx[e]) if(ei[to[e]] && seen[to[e]] == tempo && cp[e] - fl[e] > eps && lv[to[e]] == lv[s] - 1)
			if(num rf = dfs(to[e], t, min(f, cp[e] - fl[e]))) {
				fl[e] += rf;
				fl[e ^ 1] -= rf;
				return rf;
			}
		return 0;
	}
	// public $
	num max_flow(int s, int t) {
		num fl = 0;
		while (bfs(s, t)) for(num f; (f = dfs(s, t, numeric_limits<num>::max())); fl += f);
		return fl;
	}
	void add_edge(int a, int b, num c, num rc=0) {
		to[en] = b; nx[en] = hd[a]; fl[en] = 0; cp[en] = c; hd[a] = en++;
		to[en] = a; nx[en] = hd[b]; fl[en] = 0; cp[en] = rc; hd[b] = en++;
	}
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }
	void init(int n=N) { en = 2; memset(hd, 0, sizeof(int) * n); } // resets all
};

dinic d;
int n, b, r;
int x[N], y[N];
ll sq(ll x) { return x * x; }
ll dist2(int i, int j) {
	return sq(x[i] - x[j]) + sq(y[i] - y[j]);
}

bool ok(ll mn) {
	int i, j;
	d.init(b + r + 2);
	int s = b + r, t = b + r + 1;
	for(i = 0; i < b; i++) d.add_edge(s, i, 1);
	for(i = 0; i < r; i++) d.add_edge(b + i, t, 1);
	for(i = 0; i < b; i++)
		for(j = b; j < b + r; j++)
			if(dist2(i, j) < mn)
				d.add_edge(i, j, 1e9);
	return b + r - d.max_flow(s, t) >= n;
}

int main() {
	scanf("%d %d %d", &n, &b, &r);
	for(int i = 0; i < b + r; i++) scanf("%d %d", &x[i], &y[i]);
	ll l = 0, r = 20001 * 20001;
	while(l < r) {
		ll m = (l + r + 1) / 2;
		if(ok(m)) l = m;
		else r = m - 1;
	}
	printf("%.10f\n", sqrt(l));

}

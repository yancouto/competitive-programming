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

typedef int num; const int N = 112345; const int M = 312345 * 2; const num eps = 0;
struct dinic {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M]; num fl[M], cp[M]; int en = 2; int tempo = 0;
	void reset(int n=N) { en = 2; memset(hd, 0, sizeof(int) * n); } // resets all
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }
	void add_edge(int a, int b, num c, num rc=0) {
		to[en] = b; nx[en] = hd[a]; fl[en] = 0; cp[en] = c; hd[a] = en++;
		to[en] = a; nx[en] = hd[b]; fl[en] = 0; cp[en] = rc; hd[b] = en++;
	}
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
	num max_flow(int s, int t) {
		num fl = 0;
		while (bfs(s, t)) for(num f; (f = dfs(s, t, numeric_limits<num>::max())); fl += f);
		return fl;
	}
};
dinic d;


int mrk[N];
void go(int u) {
	if(mrk[u]) return;
	mrk[u] = 1;
	for(int e = d.hd[u]; e; e = d.nx[e])
		if(d.cp[e] - d.fl[e] > 0)
			go(d.to[e]);
}


int main() {
#ifdef ONLINE_JUDGE
	freopen("highways.in", "r", stdin);
	freopen("highways.out", "w", stdout);
#endif
	int n, m, k;
	int i, j;
	scanf("%d %d %d", &n, &m, &k);
	int s = n + m, t = n + m + 1;
	for(i = 0; i < n; i++) d.add_edge(s, i, k);
	for(i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b); a--; b--;
		d.add_edge(a, i + n, 1e8);
		d.add_edge(b, i + n, 1e8);
		d.add_edge(i + n, t, 1);
	}
	for(i = 0; i < n; i++) {
		d.reset_flow();
		d.add_edge(i, t, 1e8);
		int val = d.max_flow(s, t) - m;
		//printf("fix %d val %d\n", i, val);
		//for(i = 0; i <= t; i++)
		//	for(int e = d.hd[i]; e; e = d.nx[e])
		//		printf("%d->%d: %d/%d\n", i, d.to[e], d.fl[e], d.cp[e]);
		//return 0;
		if(val < k) {
			puts("Redundant");
			vector<int> S;
			go(s);
			for(i = 0; i < n; i++)
				if(!mrk[i])
					S.pb(i + 1);
			printf("%d\n", int(S.size()));
			sort(S.begin(), S.end());
			for(int x : S)
				printf("%d ", x);
			putchar('\n');
			return 0;
		}
		d.cp[d.en - 1] = d.cp[d.en - 2] = 0;
	}
	puts("OK");
}

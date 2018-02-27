#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

typedef long double num;
const int N = 212;
const int M = 112345 * 2;
const num eps = 1e-8;

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
			if(ei[to[e]] && cp[e] - fl[e] > eps && lv[to[e]] == lv[s] - 1)
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
int e_;
num a, v;

num bk, bk2;
num get_val(num m) {
	d.reset_flow();
	d.cp[e_] = m;
	assert(d.max_flow(0, 3) >= m - 1e-6);
	bk2 = d.max_flow(1, 3);
	bk = (pow(m, 1. - a) * pow(bk2 / v, a));
	//printf("get_val(%.3f) ot %.3f = %.3f\n", m, ot / v, bk);
	return bk;
}

num f[M], w[M];

int mrk[N];

num dfs(int u, bool fu, num f) {
	if(u == 3) return f;
	if(u == 1) fu = true;
	for(int e = d.hd[u]; e; e = d.nx[e])
		if(d.cp[e] > d.fl[e] + eps) {
			num rf = dfs(d.to[e], fu, min(f, d.cp[e] - d.fl[e]));
			assert(rf);
			d.fl[e] += rf;
			if(fu) {
				::f[e] += rf / v;
				::f[e ^ 1] -= rf / v;
			} else {
				w[e] += rf;
				w[e ^ 1] -= rf;
			}
			mrk[u] = 0;
			return rf;
		}
	return 0;
}

int main() {
	int i, n, m;
	cin >> n >> m;
	cin >> v >> a;
	for(i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		d.add_edge(a, b, c, c);
	}
	d.add_edge(0, 2, 30000);
	e_ = d.en - 2;
	num l = 0, r = d.max_flow(0, 3);
	//printf("mx %.3f\n", r);
	for(int bb = 0; bb < 70; bb++) {
		num m1 = (2. * l + r) / 3.;
		num m2 = (l + 2. * r) / 3.;
		if(get_val(m1) < get_val(m2))
			l = m1;
		else
			r = m2;
	}
	//for(i = 2; i < d.en; i += 2)
	//	printf("%.3f / %.3f\n", d.fl[i], d.cp[i]);
	for(i = 2; i < d.en; i++) {
		d.cp[i] = d.fl[i];
		d.fl[i] = 0;
	}
	d.add_edge(0, 1, bk2);
	while(dfs(0, 0, 1./0.));
	for(i = 2; i < d.en - 4; i += 2)
		printf("%.15f %.15f\n", double(f[i]), double(w[i]));
	printf("%.15f\n", double(bk));
}

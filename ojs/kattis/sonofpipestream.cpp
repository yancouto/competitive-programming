#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef long double num;
const int N = 1123;
const int M = 112345 * 2;
const num eps = 1e-9;

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

num v, a;
int e_;

num W_;
num val;
num get_val(num Fv) {
	d.cp[e_] = Fv;
	d.reset_flow();
	d.max_flow(0, 3);
	W_ = d.max_flow(2, 3);
	return (val = powl(Fv / v, a) * powl(W_, 1. - a));
}

num F[M], W[M];
int seen[N], tempo;

num go(int u, int sz, bool fu, num f) {
	if(u == 3) return f;
	if(sz == 1) fu = (u == 1);
	seen[u] = tempo;
	for(int e = d.hd[u]; e; e = d.nx[e])
		if(seen[d.to[e]] != tempo && d.cp[e] - d.fl[e] > eps)
			if(num rf = go(d.to[e], sz + 1, fu, min(f, d.cp[e] - d.fl[e]))) {
				d.fl[e] += rf;
				if(fu) {
					F[e] += rf / v;
					F[e ^ 1] -= rf / v;
				} else {
					W[e] += rf;
					W[e ^ 1] -= rf;
				}
				return rf;
			}
	return 0;
}

int main() {
	int n, m, i;
	cin >> n >> m >> v >> a;
	for(i = 0; i < m; i++) {
		int a, b; num c;
		cin >> a >> b >> c;
		d.add_edge(a, b, c, c);
	}
	d.add_edge(0, 1, 100000);
	e_ = d.en - 2;
	num l = 0, r = d.max_flow(0, 3);
	for(int bb = 0; bb < 80; bb++) {
		num m1 = (2. * l + r) / 3.;
		num m2 = (l + 2. * r) / 3.;
		if(get_val(m1) < get_val(m2))
			l = m1;
		else
			r = m2;
	}
	cout << setprecision(15);
	for(i = 2; i < d.en; i++)
		d.cp[i] = d.fl[i];
	d.reset_flow();
	d.add_edge(0, 2, W_, -1);
	for(tempo++; go(0, 0, false, 1./0.); tempo++);
	for(int i = 2; i < d.en - 4; i += 2)
		cout << F[i] << ' ' << W[i] << endl;
	cout << val << endl;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

typedef int num;
const int N = 11234;
const int M = 112345 * 2;
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
		//printf("(%d->%d) cp %d\n", a, b, c);
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
int vn = 0;
int l[N], r[N], need[N], c[N << 2];

int main() {
	int i, j, n, m;
	scanf("%d %d", &n, &m);
	int cn = 0;
	for(i = 0; i < n; i++) {
		scanf("%d %d %d", &l[i], &r[i], &need[i]);
		c[cn++] = l[i];
		c[cn++] = r[i];
	}
	sort(c, c + cn);
	cn = unique(c, c + cn) - c;
	int s = vn++; int t = vn++;
	int inter = vn;
	for(i = 0; i < cn - 1; i++) {
		//printf("[%d, %d]\n", c[i], c[i + 1] - 1);
		d.add_edge(s, vn++, m * (c[i + 1] - c[i]));
	}
	//puts("=====");
	for(i = 0; i < n; i++) {
		//printf("[%d, %d]\n", c[i], c[i + 1] - 1);
		int i_v = vn++;
		d.add_edge(i_v, t, need[i]);
		for(j = 0; j < cn - 1; j++)
			if(l[i] <= c[j] && r[i] >= c[j + 1] - 1)
				d.add_edge(inter + j, i_v, c[j + 1] - c[j]);
	}
	//puts("=====");
	int fl = d.max_flow(s, t);
	//printf("fl %d\n", fl);
	if(fl == accumulate(need, need + n, 0)) puts("YES");
	else puts("NO");
}

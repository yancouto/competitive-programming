#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

namespace f {
	const int maxv = 50 * 50 + 2 + 50 * 50 * 25 + 100000 + 100000;
	const int maxe = (50 * 50 + 100000 * 6 + 50 * 51 * 26 * 2) * 2;
	typedef ll num;
	num inf = LLONG_MAX;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv], cr[maxv];
	num cp[maxe], fl[maxe];


	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b= 0;
		qu[b++] = s; cr[s] = es[s];
		while(a<b) {
			for(int i = es[qu[a]]; i != -1; i = nx[i]) {
				if (cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					cr[to[i]] = es[to[i]];
					if (to[i] == t) return true;
				}
			}
			a++;
		}
		return false;
	}

	num dfs(int u, int t, num mx) {
		if(u == t) return mx;
		for (int &i = cr[u]; i != -1; i = nx[i]) {
			if (cp[i] > fl[i] && lv[to[i]] == lv[u]+1)
				if(num a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
					fl[i] += a;
					fl[i^1] -= a;
					return a;
				}
		}
		return 0;
	}

	num max_flow(int s, int t) {
		num fl = 0, a;
		while(bfs(s,t))
			while(a = dfs(s,t,inf))
				fl += a;
		return fl;
	}

	void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int)*n); }
	void reset_flow() { memset(fl, 0, sizeof(num)*en); }
	void add_edge(int a, int b, num c, num rc = 0) {
		//printf("%d %d", a, b);
		//if(c != inf) printf(" %lld", c);
		//putchar('\n');
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
};


int v[59][59][10][10], en = 0;

int main () {
	int i, n, m, k, j, li, lj;
	int t, b, l, r, x;
	scanf("%d %d %d", &n, &m, &k);
	f::reset_all();
	for(i = n - 1; i >= 0; i--)
		for(j = m - 1; j >= 0; j--) {
			for(li = 0; i + (1 << li) - 1 < n; li++)
				for(lj = 0; j + (1 << lj) - 1 < m; lj++) {
					//printf("At (%d, %d) with %d and %d = %d\n", i, j, 1 << li, 1 << lj, en);
					v[i][j][li][lj] = en++;
					if(li) {
						f::add_edge(v[i][j][li][lj], v[i][j][li - 1][lj], f::inf);
						f::add_edge(v[i][j][li][lj], v[i + (1 << (li - 1))][j][li - 1][lj], f::inf);
					} else if(lj) {
						f::add_edge(v[i][j][li][lj], v[i][j][li][lj - 1], f::inf);
						f::add_edge(v[i][j][li][lj], v[i][j + (1 << (lj - 1))][li][lj - 1], f::inf);
					}
				}
		}
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			scanf("%d", &x);
			f::add_edge(v[i][j][0][0], f::n - 1, x);
		}


	for(i = 0; i < k; i++) {
		scanf("%d %d %d %d %d", &t, &b, &l, &r, &x); t--; b--; l--; r--;
		f::add_edge(f::n - 2, en, x);
		li = 31 - __builtin_clz(b - t + 1);
		lj = 31 - __builtin_clz(r - l + 1);
		//printf("%d->%d and %d->%d\n", b - t + 1, li, r - l + 1, lj);
		f::add_edge(en, v[t][l][li][lj], f::inf);
		if((b - t + 1) != (1 << li)) f::add_edge(en, v[b - (1 << li) + 1][l][li][lj], f::inf);
		if((r - l + 1) != (1 << lj)) f::add_edge(en, v[t][r - (1 << lj) + 1][li][lj], f::inf);
		if(((b - t + 1) != (1 << li)) && ((r - l + 1) != (1 << lj))) f::add_edge(en, v[b - (1 << li) + 1][r - (1 << lj) + 1][li][lj], f::inf);
		en++;
	}

	printf("%lld\n", f::max_flow(f::n - 2, f::n - 1));
}

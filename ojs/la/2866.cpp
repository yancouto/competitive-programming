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

map<pii, int> mp;

namespace f {
	const int maxv = 200;
	const int maxe = 3123 * 2;
	typedef int num;
	num inf = INT_MAX;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv], cr[maxv];
	num cp[maxe], fl[maxe];


	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b = 0;
		qu[b++] = s; cr[s] = es[s];
		while(a < b) {
			for(int i = es[qu[a]]; i != -1; i = nx[i]) {
				if(cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					cr[to[i]] = es[to[i]];
					if(to[i] == t) return true;
				}
			}
			a++;
		}
		return false;
	}

	num dfs(int u, int t, num mx) {
		if(u == t) return mx;
		for(int &i = cr[u]; i != -1; i = nx[i])
			if(cp[i] > fl[i] && lv[to[i]] == lv[u] + 1)
				if(num a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
					fl[i] += a;
					fl[i ^ 1] -= a;
					return a;
				}
		return 0;
	}


	num max_flow(int s, int t) {
		num fl = 0, a;
		while(bfs(s, t))
			while(a = dfs(s, t, inf))
				fl += a;
		return fl;
	}

	void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }

	void add_edge(int a, int b, num c, num rc=0) {
		mp[pii(a, b)] = en;
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
}

const int N = 112;
int a[N][N], r[N], c[N], R[N], C[N];

int n, m;
int flow;
int acc;
void init() {
	int i, j;
	f::reset_all();
	for(i = 0; i < n; i++) R[i] = r[i];
	for(j = 0; j < m; j++) C[j] = c[j];
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(a[i][j] != -1) R[i] -= a[i][j], C[j] -= a[i][j];
			else
				f::add_edge(i, j + n, 100);
	for(i = 0; i < n; i++)
		f::add_edge(f::maxv - 1, i, R[i]);
	for(j = 0; j < m; j++)
		f::add_edge(j + n, f::maxv - 2, C[j]);
	flow = f::max_flow(f::maxv - 1, f::maxv - 2);
	acc = accumulate(R, R + n, 0);
	assert(flow == acc);
}
using f::fl;
using f::cp;
void exactly(int i, int j, int k) {
	int e = mp[pii(i, j + n)];
	int f = fl[e];
	fl[e] = k; fl[e ^ 1] = -k;
	int e2 = mp[pii(f::maxv - 1, i)];
	fl[e2] += k - f; fl[e2 ^ 1] -= k - f;
	int e3 = mp[pii(j + n, f::maxv - 2)];
	fl[e3] += k - f; fl[e3 ^ 1] -= k - f;
	cp[e] = k; cp[e ^ 1] = -k;
	flow += k - f;
	printf("flow %d/%d\n", flow, acc);
}

int main() {
	int i, j, k;
	while(scanf("%d %d", &n, &m) != EOF && n && m) {
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf("%d", &a[i][j]);
		for(i = 0; i < n; i++) scanf("%d", &r[i]);
		for(j = 0; j < m; j++) scanf("%d", &c[j]);
		init();
		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				if(a[i][j] != -1) { printf("%d ", a[i][j]); continue; }
				int x = -1;
				for(k = 0; k <= 100 && k <= R[i] && k <= C[j]; k++) {
					exactly(i, j, k);
					flow += f::max_flow(f::maxv - 1, f::maxv - 2);
					printf("%d/%d\n", flow, acc);
					if(flow == acc) {
						if(x == -1) x = k;
						else break;
					}
				}
				int e = mp[pii(i, j + n)];
				cp[e] = 100; cp[e ^ 1] = 0;
				if(k <= 100 && k <= R[i] && k <= C[j]) printf("-1 ");
				else printf("%d ", x);
			}
			putchar('\n');
		}

	}
}

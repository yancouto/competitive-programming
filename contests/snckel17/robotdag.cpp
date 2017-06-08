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

namespace f {
	const int maxv = 112345;
	const int maxe = 1123456 * 2;
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
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
}

int k, n, m;
int a[11234], b[11234];
bool ok(int t) {
	f::reset_all();
	for(int i = t; i >= 0; i--)
		for(int j = 0; j < m; j++)
			f::add_edge(a[j] + i * n, b[j] + (i + 1) * n, 1);
	for(int i = 0; i <= t + 1; i++)
		f::add_edge(n - 1 + i * n, f::maxv - 1, f::inf);
	f::add_edge(f::maxv - 2, 0, k);
	return f::max_flow(f::maxv - 2, f::maxv - 1) == k;
}

int main() {
	int i;
	for_tests(tn, tt) {
		scanf("%d %d %d", &n, &m, &k);
		for(i = 0; i < m; i++)
			scanf("%d %d", &a[i], &b[i]), a[i]--, b[i]--;
		if(!ok(n)) {
			puts("-1");
			continue;
		}
		int l = 0, r = n;
		while(l < r) {
			int m = (l + r) / 2;
			if(ok(m)) r = m;
			else l = m + 1;
		}
		printf("%d\n", l + 1);
	}
}

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

typedef int val; // type of flow
typedef ll num; // type of cost
const int N = 11234, M = 112345 * 2; const num eps = 0;
struct mcmf {
	int es[N], to[M], nx[M], en = 2, pai[N], seen[N], tempo, qu[N];
	val fl[M], cp[M], flow; num cs[M], d[N], tot;
	val spfa(int s, int t) {
		tempo++; int a = 0, b = 0;
		for(int i = 0; i < N; i++) d[i] = numeric_limits<num>::max();
		d[s] = 0; qu[b++] = s; seen[s] = tempo;
		while(a != b) {
			int u = qu[a++]; if(a == N) a = 0; seen[u] = 0;
			for(int e = es[u]; e; e = nx[e]) if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]] - eps) {
				d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
				if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
			}
		}
		if(d[t] == numeric_limits<num>::max()) return false;
		val mx = numeric_limits<val>::max();
		for(int u = t; u != s; u = to[pai[u]])
			mx = min(mx, cp[pai[u] ^ 1] - fl[pai[u] ^ 1]);
		tot += d[t] * val(mx);
		for(int u = t; u != s; u = to[pai[u]])
			fl[pai[u]] -= mx, fl[pai[u] ^ 1] += mx;
		return mx;
	}
	// public $
	num min_cost(int s, int t) {
		tot = 0; flow = 0;
		while(val a = spfa(s, t)) flow += a;
		return tot;
	}
	void add_edge(int u, int v, val c, num s) {
		fl[en] = 0; cp[en] = c; to[en] = v; nx[en] = es[u]; cs[en] =  s; es[u] = en++;
		fl[en] = 0; cp[en] = 0; to[en] = u; nx[en] = es[v]; cs[en] = -s; es[v] = en++;
	}
	void reset_flow() { memset(fl, 0, sizeof(val) * en); }
	void init(int n) { en = 2; memset(es, 0, sizeof(int) * n); } // XXX must be called
};

mcmf f;

int main() {
	int i, n, k, j;
	scanf("%d %d", &n, &k);
	int s = 2 * n + 2, t = 2 * n + 3;
	f.init(t + 1);
	f.add_edge(s, 1, k, 0);
	f.add_edge(1, t, k, 0);
	for(i = 0; i < n; i++) {
		for(j = i + 1; j <= n; j++) {
			int x;
			scanf("%d", &x);
			f.add_edge(2 * i + 1, 2 * j, 1, x);
		}
		f.add_edge(2 * i, 2 * i + 1, 1, -1e9);
		f.add_edge(2 * i + 1, t, 1, 0);
	}
	f.add_edge(2 * n, 2 * n + 1, 1, -1e9);
	f.add_edge(2 * n + 1, t, 1, 0);
	ll x = f.min_cost(s, t) + ll(1e9) * ll(n);
	printf("%lld\n", x);
}

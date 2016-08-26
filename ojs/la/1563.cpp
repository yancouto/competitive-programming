#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

namespace f {

const int N = 100000, M = 100000 * 2;
typedef int val;
typedef double num;
int es[N], to[M], nx[M], en, pai[N];
val fl[M], cp[M];
num cs[M], d[N];
const num inf = 1e18, eps = 1e-6;
const val infv = INT_MAX;
int seen[N], tempo;
int qu[N];

num tot;
bool spfa(int s, int t) {
	tempo++;
	int a = 0, b = 0;
	for(int i = 0; i < N; i++) d[i] = inf;
	d[s] = 0;
	qu[b++] = s;
	seen[s] = tempo;
	while(a != b) {
		int u = qu[a++]; if(a == N) a = 0;
		seen[u] = 0;
		for(int e = es[u]; e != -1; e = nx[e])
			if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]] - eps) {
				d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
				if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
			}
	}
	if(d[t] == inf) return false;
	val mx = infv;
	for(int u = t; u != s; u = to[pai[u]])
		mx = min(mx, cp[pai[u] ^ 1] - fl[pai[u] ^ 1]);
	tot += d[t] * val(mx);
	for(int u = t; u != s; u = to[pai[u]])
		fl[pai[u]] -= mx, fl[pai[u] ^ 1] += mx;
	return true;
}

void init(int n) {
	en = 0;
	memset(es, -1, sizeof(int) * n);
}

void reset() {
	memset(fl, 0, sizeof(val) * en);
}

val flow;
num mncost(int s, int t) {
	tot = 0; flow = 0;
	while(spfa(s, t)) flow++;
	return tot;
}

void add_edge(int u, int v, val c, val rc, num s) {
	fl[en] = 0; cp[en] =  c; to[en] = v; nx[en] = es[u]; cs[en] =  s; es[u] = en++;
	fl[en] = 0; cp[en] = rc; to[en] = u; nx[en] = es[v]; cs[en] = -s; es[v] = en++;
}
}

int main() {
	int i, j, n, m, x, tt = 0; double v;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		f::init(n + m + n * m  + 100);
		int S = n + m + n * m + 50;
		int T = n + m + n * m + 70;
		int off = n + n * m;
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			f::add_edge(S, i, x, 0, 0);
		}
		for(i = 0; i < m; i++) {
			scanf("%d", &x);
			f::add_edge(off + i, T, x, 0, 0);
		}
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				scanf("%lf", &v);
				if(v < -.5) continue;
				f::add_edge(i, n + i * m + j, f::infv, 0, v);
				f::add_edge(n + i * m + j, off + j, 1e8, 0, 0);
			}
		double mn = f::mncost(S, T);
		for(i = 0; i < f::en; i++)
			f::fl[i] = 0,
			f::cs[i] *= -1.;
		printf("Problem %d: %.2f to %.2f\n", ++tt, mn, -f::mncost(S, T));
	}
}

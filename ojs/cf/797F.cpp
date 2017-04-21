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
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

namespace f {

const int N = 11234, M = (5009 * 5009 + 2 * 5009) * 2;
typedef int val;
typedef ll num;
int es[N], to[M], nx[M], en, pai[N];
val fl[M], cp[M];
num cs[M], d[N];
const num inf = 1e18, eps = 0;
const val infv = INT_MAX;
int seen[N], tempo;
int qu[N];

num tot;
val spfa(int s, int t) {
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
	return mx;
}

void init(int n) {
	en = 0;
	memset(es, -1, sizeof(int) * n);
}

val flow;
num mncost(int s, int t) {
	tot = 0; flow = 0;
	while(val a = spfa(s, t)) flow += a;
	return tot;
}

void add_edge(int u, int v, val c, num s) {
	fl[en] = 0; cp[en] = c; to[en] = v; nx[en] = es[u]; cs[en] =  s; es[u] = en++;
	fl[en] = 0; cp[en] = 0; to[en] = u; nx[en] = es[v]; cs[en] = -s; es[v] = en++;
}
}

int n;
const int N = 5123;
int x[N], p[N], c[N], P[N];

int main() {
	srand(time(NULL));
	int i, j, m;
	scanf("%d %d", &n, &m);
	//for(i = 0; i < n; i++) scanf("%d", &x[i]);
	//for(i = 0; i < m; i++) scanf("%d %d", &p[i], &c[i]);
	for(i = 0; i < n; i++) x[i] = rand() % 1000000000;
	for(i = 0; i < m; i++) p[i] = rand() % 1000000000, c[i] = rand() % n;
	f::init(n + m + 2);
	for(i = 0; i < m; i++) P[i] = i;
	for(i = 0; i < n; i++)
		f::add_edge(n + m, i, 1, 0);
	for(i = 0; i < n; i++) {
		sort(P, P + m, [i](int a, int b) { return abs(x[i] - p[a]) > abs(x[i] - p[b]); });
		for(j = 0; j < m; j++)
			f::add_edge(i, n + P[j], 1, abs(p[P[j]] - x[i]));
	}
	for(i = 0; i < m; i++)
		f::add_edge(n + i, n + m + 1, c[i], 0);
	if(accumulate(c, c + m, 0) < n) puts("-1");
	else printf("%lld\n", f::mncost(n + m, n + m + 1));
}

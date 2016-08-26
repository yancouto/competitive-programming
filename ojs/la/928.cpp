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

const int N = 1000, M = 100000 * 2;
typedef int val;
typedef int num;
int es[N], to[M], nx[M], en, pai[N];
val fl[M], cp[M];
num cs[M], d[N];
const num inf = 1e8;
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
			if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]]) {
				d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
				if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
			}
	}
	if(d[t] == inf) return false;
	tot += d[t];
	int u = t;
	while(u != s) {
		fl[pai[u]]--;
		fl[pai[u] ^ 1]++;
		u = to[pai[u]];
	}
	return true;
}

void init(int n) {
	en = 0;
	memset(es, -1, sizeof(int) * n);
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

inline int vin(int u) { return u << 1; }
inline int vout(int u) { return (u << 1) | 1; }

int main() {
	int i, n, m, a, b, c, tt = 0;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		f::init(2*n + 100);
		int S = 2*n + 50, T = 2*n + 70;
		for(i = 0; i < n; i++)
			f::add_edge(vin(i), vout(i), 1, 0, 0);
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			f::add_edge(vout(a), vin(b), 1, 0, c);
		}
		f::add_edge(S, vout(0), 2, 0, 0);
		f::add_edge(vin(n - 1), T, 2, 0, 0);
		f::mncost(S, T);
		printf("Instance #%d: ", ++tt);
		if(f::flow < 2) puts("Not possible");
		else printf("%d\n", f::tot);
	}
}

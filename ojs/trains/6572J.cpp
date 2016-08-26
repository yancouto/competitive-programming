// n sei fazer direito
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

const int N = 20000, M = 200000;
typedef int val;
typedef int num;
int es[N], to[M], nx[M], en, pai[N];
val fl[M], cp[M], d[N];
num cs[M];
const num inf = 1000000000;
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


val flow = 0;
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

int q[200];
int main() {
	int i, j, n, k, m, x, g, i2;
	scanf("%d %d %d", &n, &k, &m);
	f::init(f::N);
	for(i = 1; i <= m; i++)
		scanf("%d", &q[i]);
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		for(j = 0; j < x; j++) {
			scanf("%d", &g);
			for(i2 = 0; i2 <= m; i2++) {
				printf("girl %d on day %d to girl %d on day %d\n", i2, i, g, i + 1);
				f::add_edge(i2 + i * (m + 1), g + (i + 1) * (m + 1), 1, 0, (i2 != g) * q[g]);
			}
		}
		f::add_edge(i * (m + 1), (i + 1) * (m + 1), max(0, k - x), 0, 0);
	}
	f::add_edge(f::N - 2, 0, k, 0, 0);
	for(i = 1; i <= m; i++)
		f::add_edge(i + n * (m + 1), f::N - 1, 1, 0, 0);
	printf("%d\n", f::mncost(f::N - 2, f::N - 1));
}

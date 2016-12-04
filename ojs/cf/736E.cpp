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

int n, m;
int a[3123];

namespace f {

const int N = 5000000 + 10000, M = (13500000 + 10000) * 2;
typedef short sh;
typedef int val;
typedef int num;
int es[N], to[M], nx[M], en, pai[N];
sh fl[M];
sh d[N];
const num inf = 1e8, eps = 0;
const val infv = INT_MAX;
sh seen[N], tempo, s2[N];
int qu[N];

inline int cost(int u, int e) { return to[e] == N-2 && u >= n; }
inline int cap(int u, int e) {
	if(e & 1) return 0;
	if(to[e] != N - 2) return 2;
	return a[u];
}
inline int nex(int u, int e) {
	if(u == N - 1) {
		assert((e % 6) == 0);
		if(e/6 + 1 == (m * (m - 1)) / 2) return -1;
		return e + 6;
	} else if(u >= m && u < N - 2) {
		if(e & 1) return e + 1;
		if((e - 2) % 6 == 0) return e + 2;
		return -1;
	} else if(u < m) {
		if(e == 3 * m * (m - 1) + u * 2) return -1;
		if((e - 3) % 6 == 0) {
			if((e - 3) / 6 == n - 1 - u) return 3 * m * (m - 1) + u * 2;
			else return e + 6;
		} else {
			if((e - 5) / 6 ==  u - 1) return 3 * (u * m - (u * (u + 1)) / 2);
			else return e + 6;
		}
	} else {
		if(e == 3 * m * (m - 1) + 2 * m - 1) return -1;
		else return e + 2;
	}
}

num tot = 0;
val spfa(int s, int t) {
	tempo++;
	if(tempo == 0) tempo++;
	int a = 0, b = 0;
	d[s] = 0;
	qu[b++] = s;
	seen[s] = tempo;
	while(a != b) {
		int u = qu[a++]; if(a == N) a = 0;
		seen[u] = 0;
		for(int e = es[u]; e != -1; e = nx[e])
			if(cap(u,e) - fl[e] > val(0) && (s2[to[e]] != tempo || d[u] + cost(u,e) < d[to[e]] - eps)) {
				s2[to[e]] = tempo;
				d[to[e]] = d[u] + cost(u,e); pai[to[e]] = e ^ 1;
				if(seen[to[e]] != tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
			}
	}
	if(s2[t] != tempo) return false;
	val mx = infv;
	for(int u = t; u != s; u = to[pai[u]])
		mx = min(mx, cap(to[pai[u]], pai[u] ^ 1) - fl[pai[u] ^ 1]);
	tot += d[t] * val(mx);
	for(int u = t; u != s; u = to[pai[u]])
		fl[pai[u]] -= mx, fl[pai[u] ^ 1] += mx;
	return mx;
}

void init(int n) {
	en = 0;
	memset(es, -1, sizeof(int) * n);
}

val flow = 0;
num mncost(int s, int t) {
	tot = 0; flow = 0;
	while(val a = spfa(s, t)) flow += a;
	return tot;
}

void add_edge(int u, int v, val c, num s) {
	fl[en] = 0; to[en] = v; nx[en] = es[u]; es[u] = en++;
	fl[en] = 0; to[en] = u; nx[en] = es[v]; es[v] = en++;
}
}

char g[3123][3123];

int main() {
	int i, j;
	scanf("%d %d", &m, &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	for(i = n; i < m; i++) a[i] = a[i - 1];
	f::init(f::N);
	int s = f::N - 1, t = f::N - 2;
	int ct = 0;
	for(i = 0; i < m; i++)
		for(j = i + 1; j < m; j++) {
			int x = m + (ct++);
			f::add_edge(s, x, 2, 0);
			f::add_edge(x, i, 2, 0);
			f::add_edge(x, j, 2, 0);
		}
	for(i = 0; i < m; i++)
		f::add_edge(i, t, a[i], (i >= n));
	int cost = f::mncost(s, t);
	int flow = f::flow;
	//printf("flow %d cost %d\n", flow, cost);
	if(flow == m * (m - 1) && cost == m * (m - 1) - accumulate(a, a + n, 0)) {
		puts("yes");
		ct = 0;
		for(i = 0; i < m; i++)
			for(j = i + 1; j < m; j++) {
				int x = m + (ct++);
				int ej = f::es[x], ei = f::nx[f::es[x]];
				if(f::fl[ei] == 1) g[i][j] = 'D', g[j][i] = 'D';
				else {
					g[i][j] = 'W'; g[j][i] = 'L';
					if(f::fl[ei] == 0) swap(g[i][j], g[j][i]);
				}
			}
		for(i = 0; i < m; i++) g[i][i] = 'X';
		for(i = 0; i < m; i++)
			for(j = 0; j < m; j++) {
				putchar(g[i][j]);
				if(j == m - 1) putchar('\n');
			}
	} else puts("no");
}

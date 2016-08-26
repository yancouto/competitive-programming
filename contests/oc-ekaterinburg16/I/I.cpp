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

const int N = 100, M = 112345;
typedef int val;
typedef int num;
int es[N], to[M], nx[M], en, pai[N];
val fl[M], cp[M], d[N];
num cs[M], dp[N];
const num inf = 1e9, eps = 0;
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
const int N = 112;
int M[N][N];
int a[N][N];


int n, m, k, c, q;
int go(int A[]) {
	f::init(40);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < k; j++) {
			if(M[i][j] == INT_MAX) continue;
			f::add_edge(i, j + n, 1, M[i][j] * A[j]);
		}
	for(int i = 0; i < n; i++) f::add_edge(35, i, 1, 0);
	for(int j = 0; j < k; j++) if(A[j]) f::add_edge(j + n, 36, 1, 0);
	return f::mncost(35, 36);
}

int memo[112];
int solve(int i) {
	if(i == q) return 0;
	int &r = memo[i];
	if(r != -1) return r;
	r = INT_MAX;
	int A[112] = {0};
	for(int j = i; j < q; j++) {
		for(int g = 0; g < k; g++)
			A[g] += a[j][g];
		r = min(r, c + solve(j + 1) + go(A));
	}
	return r;
}


int main() {
	int i, j, s, t, w;
	scanf("%d %d %d %d", &n, &k, &c, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < k; j++)
			M[i][j] = INT_MAX;
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &s, &t, &w); s--; t--;
		M[s][t] = w;
	}
	scanf("%d", &q);
	for(i = 0; i < q; i++)
		for(j = 0; j < k; j++)
			scanf("%d", &a[i][j]);
	memset(memo, -1, sizeof memo);
	printf("%d\n", solve(0));
}

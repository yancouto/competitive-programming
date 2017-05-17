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

const int N = 1212, M = 41234 * 2;
typedef int val;
typedef int num;
int es[N], to[M], nx[M], en, pai[N];
val fl[M], cp[M];
num cs[M], d[N];
const num inf = 1e8, eps = 0;
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

int n, k;

const int N = 112;
struct card {
	int p, c, l;
} c[N];
const int M = 1123456;
int comp[M];

bool ok(int L) {
	vector<card> cs, c1;
	int i, j;
	for(i = 0; i < n; i++) {
		if(c[i].l > L) continue;
		if(c[i].c == 1) c1.pb(c[i]);
		else cs.pb(c[i]);
	}
	sort(c1.begin(), c1.end(), [](card a, card b) { return a.p > b.p; });
	while(c1.size() > 1) c1.pop_back();
	for(card cc : c1) cs.pb(cc);
	f::init(cs.size() + 2);
	ll all = 0;
	for(i = 0; i < cs.size(); i++) {
		all += cs[i].p;
		if(cs[i].c & 1) {
			f::add_edge(i, cs.size() + 1, 1, 0);
			continue;
		}
		f::add_edge(cs.size(), i, 1, 0);
		for(j = 0; j < cs.size(); j++) {
			if(!(cs[j].c & 1) || comp[cs[i].c + cs[j].c]) continue;
			debug("%d, %d : %d + %d = %d\n", i, j, cs[i].c, cs[j].c, comp[cs[i].c + cs[j].c]);
			f::add_edge(i, j, 1, min(cs[i].p, cs[j].p));
		}
	}
	int power = all - f::mncost(cs.size(), cs.size() + 1);
	debug("L %d -- (%d, %d)\n", L, f::flow, power);
	return power >= k;
}

// CHANGE TO MAXFLOW --- EXACTLY LIKE UNWEIGHTED VERTEX COVER
int main() {
	int i, j;
	for(i = 2; i < M; i++)
		if(!comp[i])
			for(j = i + i; j < M; j += i)
				comp[j] = 1;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++)
		scanf("%d %d %d", &c[i].p, &c[i].c, &c[i].l);
	if(!ok(100)) { puts("-1"); return 0; }
	int l = 1, r = 100;
	while(l < r) {
		int m = (l + r) / 2;
		if(ok(m)) r = m;
		else l = m + 1;
	}
	printf("%d\n", l);
}

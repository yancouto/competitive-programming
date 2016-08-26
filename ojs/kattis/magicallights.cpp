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

const int N = 300009;
vector<int> adj[N];
struct co {
	co() : a(0), b(0) {}
	co(ull aa, ull bb) : a(aa), b(bb) {}
	ull a, b;
	inline int num() { return __builtin_popcountll(a) + __builtin_popcountll(b); }
};

co operator ^ (co l, co r) {
	return co(l.a ^ r.a, l.b ^ r.b);
}

co from(int i) {
	co c;
	if(i <= 64) c.a |= (1ull << (i - 1));
	else c.b |= (1ull << (i - 65));
	return c;
}
co val[N];

struct bit {
	int s;
	co *b;
	bit() {}
	bit(int size) : s(size), b((new co[size + 3]) - 1) {for(int i = 1; i <= size + 3; i++) b[i] = co();}
	co get(int i) {
		co r;
		for(i += 1; i; i -= (i & -i))
			r = r ^ b[i];
		return r;
	}

	co add(int i, co x) {
		for(i += 1; i <= s + 3; i += (i & -i)) {
			b[i] = b[i] ^ x;
		}
	}
};

int so[N];
co& dfs(int u) {
	so[u] = 1;
	co &r = val[u];
	for(int v : adj[u]) {
		r = r ^ dfs(v);
		so[u] += so[v];
	}
	return r;
}


bit cb[N];
int vp[N], vc[N], cs[N], ch[N];
int cur; co pr[N];

bit init_bit() {
	bit b(cs[cur]);
	for(int i = 0; i < cs[cur]; i++) {
		b.add(i, pr[i]);
		b.add(i + 1, pr[i]);
	}
	return b;
}

void hld(int u) {
	vp[u] = cs[cur];
	if(vp[u] == 0) ch[cur] = u;
	pr[vp[u]] = val[u];
	vc[u] = cur;
	cs[cur]++;
	if(adj[u].empty()) { cb[cur] = init_bit(); return; }
	int ba = adj[u].front();
	for(int v : adj[u])
		if(so[v] > so[ba])
			ba = v;
	hld(ba);
	for(int v : adj[u]) {
		if(v == ba) continue;
		cur++;
		hld(v);
	}
}

co query(int u) {
	int c = vc[u];
	return cb[c].get(vp[u]);
}

int pai[N];
void upd(int u, co x) {
	while(true) {
		int c = vc[u];
		cb[c].add(0, x);
		cb[c].add(vp[u] + 1, x);
		u = ch[c];
		if(!u) return;
		u = pai[u];
	}
}

void deb() {
	for(int i = 0; i <= cur; i++) {
		printf("chain %d:\n", i);
		for(int j = 0; j < cs[i]; j++)
			printf("%llu ", cb[i].get(j).a);
		putchar('\n');
	}
}

int cc[N];
int main() {
	int i, n, q, x, k;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n; i++) {
		scanf("%d", &cc[i]);
		val[i] = from(cc[i]);
	}
	for(i = 1; i < n; i++) {
		scanf("%d", &x);
		adj[x - 1].pb(i);
		pai[i] = x - 1;
	}
	dfs(0);
	hld(0);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &k, &x); x--;
		if(k) { upd(x, from(k) ^ from(cc[x])); cc[x] = k; }
		else printf("%d\n", query(x).num());
	}
}

/*
11 1000
1 1 1 1 1 1 1 1 1 1 1
1 1 1 2 3 3 4 4 8 8
0 1
0 2
0 5
0 3
1 1
0 1
2 1
0 1
2 6
0 1
0 3
3 7
0 7
3
*/

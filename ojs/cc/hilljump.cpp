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


const int N = 112345;
typedef int num;

int en = 1;
int p[N], sz[N];
int C[N][2]; // {left, right} children
int pp[N]; bool lzswp[N];

// atualize os valores associados aos nos que podem ser calculados a partir dos filhos
inline void calc(int u) {
	sz[u] = sz[C[u][0]] + 1 + sz[C[u][1]];
}

inline void unlaze(int u) {
	if(!u) return;
	if(lzswp[u]) {
		swap(C[u][0], C[u][1]);
		if(C[u][0]) lzswp[C[u][0]] ^= 1;
		if(C[u][1]) lzswp[C[u][1]] ^= 1;
		lzswp[u] = 0;
	}
}


// Puxa o filho dir de u para ficar em sua posicao e o retorna
int rotate(int u, int dir) {
	int v = C[u][dir];
	swap(pp[v], pp[u]);
	C[u][dir] = C[v][!dir];
	if(C[u][dir]) p[C[u][dir]] = u;
	C[v][!dir] = u;
	p[v] = p[u];
	if(p[v]) C[p[v]][C[p[v]][1] == u] = v;
	p[u] = v;
	calc(u);
	calc(v);
	return v;
}

void unlz_back(int u) {
	if(!u) return;
	unlz_back(p[u]);
	unlaze(u);
}

// Traz o no u a raiz
void splay(int u) {
	unlz_back(u);
	//printf("splay(%d) %d\n", u, sz[u]);
	while(p[u]) {
		int v = p[u], w = p[p[u]];
		int du = (C[v][1] == u);
		if(!w) {
			rotate(v, du);
		} else {
			int dv = (C[w][1] == v);
			if(du == dv) {
				rotate(w, dv);
				rotate(v, du);
			} else {
				rotate(v, du);
				rotate(w, dv);
			}
		}
	}
}

// retorna o s-esimo no (0-indexed)
int find_sz(int u, int s) {
	unlaze(u);
	while(sz[C[u][0]] != s) {
		if(sz[C[u][0]] < s) {
			s -= sz[C[u][0]] + 1;
			u = C[u][1];
		} else u = C[u][0];
		unlaze(u);
	}
	splay(u);
	return u;
}

// chame isso 1 vez no inicio
void init() {
	en = 1;
}

// Cria um novo no
int new_node() {
	int i = en++;
	assert(i < N);
	pp[i] = C[i][0] = C[i][1] = p[i] = 0;
	lzswp[i] = 0;
	sz[i] = 1;
	return i;
}

int access(int u) {
	if(!u) return u;
	splay(u);
	if(int v = C[u][1]) {
		p[v] = 0;
		pp[v] = u;
		C[u][1] = 0;
	}
	calc(u);
	while(pp[u]) {
		int w = pp[u];
		splay(w);
		if(int v = C[w][1]) {
			p[v] = 0;
			pp[v] = w;
		}
		C[w][1] = u;
		p[u] = w;
		pp[u] = 0;
		calc(w);
		splay(u);
	}
	return u;
}

// retorna a raiz da arvore de u
int find_root(int u) {
	access(u);
	while(C[u][0]) { unlaze(u = C[u][0]); }
	access(u);
	return u;
}

// pai de u. pode mudar por causa de rootify
int get_parent(int u) {
	access(u);
	if(!C[u][0]) return pp[u];
	unlaze(u = C[u][0]);
	while(C[u][1]) unlaze(u = C[u][1]);
	access(u);
	return u;
}

// adiciona aresta de u para v
// v deve ser raiz de sua arvore
void link(int u, int v) {
	if(find_root(u) == find_root(v)) return;
	access(u); access(v);
	assert(C[v][0] == 0 && pp[v] == 0 && sz[v] == 1); // v deve ser raiz
	C[u][1] = v;
	p[v] = u;
	calc(u);
}

// remove o link de u para seu pai
void cut(int u) {
	access(u);
	assert(C[u][0]); // deve ter pai
	p[C[u][0]] = 0;
	C[u][0] = 0;
	calc(u);
}

// faz u ser a raiz de sua arvore.
// XXX cuidado ao misturar rootify e cut, use get_parent
void rootify(int u) {
	access(u);
	lzswp[u] = 1;
	access(u);
}

ll bit[N];

void add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

ll get(int i) {
	ll sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}

int a[N];
ll st[N]; ll sn = 0;
int n;
int par[N];

void fix(int l) {
	sn = 0;
	for(int i = min(l + 100, n); i >= l; i--) {
		while(sn && (st[sn - 1] > i + 100 || get(st[sn - 1]) <= get(i))) sn--;
		st[sn++] = i;
	}
	for(int i = l - 1; i >= l - 100 && i >= 1; i--) {
		while(sn && (st[sn - 1] > i + 100 || get(st[sn - 1]) <= get(i))) sn--;
		if(sn && par[i] != st[sn - 1]) {
			if(par[i]) cut(i);
			link(st[sn - 1], i);
			par[i] = st[sn - 1];
		} else if(!sn && par[i]) {
			cut(i);
			par[i] = 0;
		}
		st[sn++] = i;
	}
}

int main() {
	int i, q;
	int op, k, l, r, x;
	scanf("%d %d", &n, &q);
	for(i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(i = 1; i <= n; i++) add(i, a[i]), add(i + 1, -a[i]);
	for(i = 1; i <= n; i++) new_node();
	for(i = n; i > 0; i--) {
		while(sn && (st[sn - 1] > i + 100 || a[st[sn - 1]] <= a[i])) sn--;
		if(sn) link(st[sn - 1], i), par[i] = st[sn - 1];
		st[sn++] = i;
	}
	while(q--) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d %d", &i, &k);
			access(i);
			if(k >= sz[i]) k = sz[i] - 1;
			k = sz[i] - 1 - k;
			printf("%d\n", find_sz(i, k));
		} else {
			scanf("%d %d %d", &l, &r, &x);
			add(l, x);
			add(r + 1, -x);
			fix(l);
			fix(r + 1);
		}
	}
}

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
const int N = 312345;
typedef long long ll;

typedef int num;

int en = 1;
int Y[N], sz[N], L[N], R[N];
num X[N];

int B[N], Bacc[N];

int lzb[N], lzx[N];

void unlaze(int);

// atualize os valores associados aos nos que podem ser calculados a partir dos filhos
void calc(int u) {
	unlaze(L[u]); unlaze(R[u]);
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
	Bacc[u] = Bacc[L[u]] ^ B[u] ^ Bacc[R[u]];
	//pacc[u] = pacc[L[u]] ^ B[u] ^ pacc[R[u]];
}

void unlaze(int u) {
	if(!u) return;
	// Faca seus lazy aqui
	if(sz[u] & 1) Bacc[u] ^= lzb[u];
	B[u] ^= lzb[u];
	X[u] -= lzx[u];
	if(L[u]) lzb[L[u]] ^= lzb[u], lzx[L[u]] += lzx[u];
	if(R[u]) lzb[R[u]] ^= lzb[u], lzx[R[u]] += lzx[u];
	lzx[u] = lzb[u] = 0;
}

int mn(int u) {
	unlaze(u);
	while(L[u])
		unlaze(u = L[u]);
	return u;
}

int mx(int u) {
	unlaze(u);
	while(R[u])
		unlaze(u = R[u]);
	return u;
}


// divida a treap entre (valores <= x, valores > x)
void split_val(int u, num x, int &l, int &r) {
	unlaze(u);
	if(!u) return (void) (l = r = 0);
	if(X[u] <= x) split_val(R[u], x, l, r), R[u] = l, l = u;
	else split_val(L[u], x, l, r), L[u] = r, r = u;
	calc(u);
}

// divida a treap entre (primeiros s elementos, resto)
void split_sz(int u, int s, int &l, int &r) {
	unlaze(u);
	if(!u) return (void) (l = r = 0);
	if(sz[L[u]] < s) split_sz(R[u], s - sz[L[u]] - 1, l, r), R[u] = l, l = u;
	else split_sz(L[u], s, l, r), L[u] = r, r = u;
	calc(u);
}

// junte duas treaps, sendo que elementos l <= elementos r
int merge(int l, int r) {
	unlaze(l); unlaze(r);
	if(!l || !r) return l + r;
	int u;
	if(Y[l] > Y[r]) R[l] = merge(R[l], r), u = l;
	else L[r] = merge(l, L[r]), u = r;
	calc(u);
	return u;
}

// chame isso 1 vez no inicio. Para implicita e so nao usar o X
void init(int n=N-1) {
	en = 1;
	for(int i = 1; i <= n; i++) Y[i] = i, sz[i] = 1, L[i] = R[i] = 0;
	random_shuffle(Y + 1, Y + n + 1);
}

void add(int &root, int h, int x) {
	int a, b, c;
	split_val(root, h - 1, a, c);
	b = en++;
	X[b] = h; B[b] = x; Bacc[b] = x;
	root = merge(a, merge(b, c));
}

vector<int> g;
int ra, x, k;
void go(int u) {
	unlaze(u);
	if(!u) return;
	go(L[u]);
	g.pb(u);
	go(R[u]);
	X[u] -= x;
	B[u] ^= k;
	Bacc[u] = B[u];
	sz[u] = 1;
	L[u] = R[u] = 0;
}

void go2(int &ro, int l, int r) {
	if(l > r) return;
	int m = (l + r) / 2;
	int a, b;
	split_val(ro, X[g[m]], a, b);
	go2(a, l, m - 1);
	go2(b, m + 1, r);
	ro = merge(a, merge(g[m], b));
}

int main() {
	int i, n, q, op;
	scanf("%d", &n);
	init();
	int root = 0;
	int a, b, a2, b2, c;
	for(i = 1; i <= n; i++) {
		scanf("%d %d", &a, &b);
		add(root, a, b);
	}
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &op, &x);
		if(op == 1) {
			scanf("%d", &k);
			split_val(root, x - 1, a, b);
			if(b == 0) { root = a; continue; }
			split_val(b, 2 * x - 1, b, c);
			if(c) {
				lzb[c] = k; lzx[c] = x;
				unlaze(c);
			}
			go(b);
			go2(a, 0, int(g.size()) - 1);
			g.clear();
			root = merge(a, c);
		} else {
			split_val(root, x - 1, a, b);
			printf("%d\n", Bacc[b]);
			root = merge(a, b);
		}
	}

}

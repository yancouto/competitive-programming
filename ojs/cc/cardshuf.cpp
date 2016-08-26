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
const int N = 100009;

int val[N], L[N], R[N], swp[N], y[N], sz[N];

int root;
void ac(int u) {
	if(swp[u]) {
		swap(L[u], R[u]);
		swp[L[u]] = !swp[L[u]];
		swp[R[u]] = !swp[R[u]];
		swp[u] = false;
	}
}

void calc(int u) {
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
}

pii split(int u, int s) {
	if(!u) return pii(0, 0);
	ac(u);
	if(s > sz[L[u]]) {
		pii p = split(R[u], s - sz[L[u]] - 1);
		R[u] = p.fst; calc(u);
		return pii(u, p.snd);
	} else {
		pii p = split(L[u], s);
		L[u] = p.snd; calc(u);
		return pii(p.fst, u);
	}
}

int merge(int l, int r) {
	if(!l || !r) return max(l, r);
	ac(l); ac(r);
	if(y[l] > y[r]) R[l] = merge(R[l], r);
	else L[r] = merge(l, L[r]);
	int u = y[l] > y[r]? l : r;
	calc(u);
	return u;
}

void add(int i) {
	sz[i] = 1;
	root = merge(root, i);
}

int inv(int u) {
	swp[u] = !swp[u];
	return u;
}

void shuf(int a, int b, int c) {
	pii p1 = split(root, a);
	pii p2 = split(p1.snd, b); 
	root = merge(p1.fst, p2.snd);	
	pii p3 = split(root, c);
	root = merge(p3.fst, merge(inv(p2.fst), p3.snd));
}

int main() {
	int i, n, m, a, b, c;
	for(i = 0; i < N; i++) y[i] = i;
	random_shuffle(y, y + N);
	scanf("%d %d", &n, &m);
	for(i = 1; i <= n; i++) {
		val[i] = i;
		add(i);
	}
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		shuf(a, b, c);
	}
	for(i = 0; i < n; i++) {
		pii p = split(root, 1);
		printf("%d ", val[p.fst]);
		root = p.snd;
	}
	putchar('\n');
}

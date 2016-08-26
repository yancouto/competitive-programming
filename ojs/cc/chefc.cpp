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
const int nil = N - 1;

int sz[N], f[N], L[N], R[N], val[N], y[N];

int mx(int v) { while(R[v] != nil) v = R[v]; return v; }
int mn(int v) { while(L[v] != nil) v = L[v]; return v; }

void calc(int v) {
	sz[v] = sz[L[v]] + 1 + sz[R[v]];
	f[v] = f[L[v]] + (L[v] != nil && val[mx(L[v])] != val[v]) + (R[v] != nil && val[mn(R[v])] != val[v]) + f[R[v]];
}

pii split(int root, int s) {
	if(root == nil) return pii(nil, nil);
	if(s > sz[L[root]]) {
		pii p = split(R[root], s - sz[L[root]] - 1);
		R[root] = p.fst; calc(root);
		p.fst = root;
		return p;
	} else {
		pii p = split(L[root], s);
		L[root] = p.snd; calc(root);
		p.snd = root;
		return p;
	}
}

int merge(int l, int r) {
	if(l == nil) return r;
	if(r == nil) return l;
	if(y[l] > y[r])
		R[l] = merge(R[l], r);
	else L[r] = merge(l, L[r]);
	int ro = y[l] > y[r]? l : r;
	calc(ro);
	return ro;
}

int root;
void add(int i) {
	L[i] = R[i] = nil; sz[i] = 1; f[i] = 0;
	root = merge(root, i);
}

int fun(int l, int r) {
	pii p1 = split(root, l - 1);
	pii p2 = split(p1.snd, r - l + 1);
	int v = f[p2.fst];
	root = merge(merge(p1.fst, p2.fst), p2.snd);
	return v + 1;
}

void modi(int l, int r) {
	pii p1 = split(root, l - 1);
	pii p2 = split(p1.snd, r - l + 1);
	assert(sz[p1.fst] == l - 1);
	assert(sz[p2.fst == r - l + 1]);
	root = merge(merge(p2.fst, p1.fst), p2.snd);
}

void deb(int u) {
	if(u == nil) return;
	deb(L[u]);
	printf(" %d", val[u]);
	deb(R[u]);
}

int main() {
	int i, n, m, op, l, r;
	for(i = 0; i < N; i++) y[i] = i;
	random_shuffle(y, y + N);
	for_tests(t, tt) {
		scanf("%d", &n);
		root = nil;
		for(i = 0; i < n; i++) {
			scanf("%d", &val[i]);
			add(i);
		}
		scanf("%d", &m);
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &op, &l, &r);
			if(op == 1) printf("%d\n", fun(l, r));
			else modi(l, r);
			putchar('\n');
		}
	}
}

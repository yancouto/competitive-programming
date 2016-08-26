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

const int N = 200009;
const int nil = N - 1;

int L[N], R[N], sz[N], mx[N], mn[N], val[N], vX[N], vN[N], y[N];

int root;
void calc(int u) {
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
	mx[u] = max(mx[R[u]], val[u]);
	mn[u] = min(mn[L[u]], val[u]);
	vN[u] = min(min(vN[L[u]], vN[R[u]]), min(val[u] - mx[L[u]], mn[R[u]] - val[u]));
	if(sz[u] == 1) vN[u] = modn;
	vX[u] = mx[u] - mn[u];
}

pii split_x(int root, int x) {
	if(root == nil) return pii(nil, nil);
	if(val[root] < x) {
		pii p = split_x(R[root], x);
		R[root] = p.fst;
		p.fst = root; calc(root);
		return p;
	} else {
		pii p = split_x(L[root], x);
		L[root] = p.snd; calc(root);
		p.snd = root;
		return p;
	}
}

pii split(int root, int s) {
	if(root == nil) return pii(nil, nil);
	if(s > sz[L[root]]) {
		pii p = split(R[root], s - sz[L[root]] - 1);
		R[root] = p.fst;
		p.fst = root; calc(root);
		return p;
	} else {
		pii p = split(L[root], s);
		L[root] = p.snd;
		p.snd = root; calc(root);
		return p;
	}
}

int merge(int l, int r) {
	if(l == nil) return r;
	if(r == nil) return l;
	if(y[l] > y[r]) R[l] = merge(R[l], r);
	else L[r] = merge(l, L[r]);
	int u = y[l] > y[r]? l : r;
	calc(u);
	return u;
}

int cur;
void add(int x) {
	pii p = split_x(root, x);
	if(mn[p.snd] == x) return (void)(root = merge(p.fst, p.snd));
	val[cur] = x; sz[cur] = 1; vN[cur] = INT_MAX; L[cur] = R[cur] = nil;
	root = merge(merge(p.fst, cur++), p.snd); 
}

void rem(int x) {
	pii p = split_x(root, x);
	pii p2 = split_x(p.snd, x + 1);
	root = merge(p.fst, p2.snd);
}

int f(int l, int r, int V[]) {
	if(l == r) return -1;
	pii p1 = split(root, l);
	pii p2 = split(p1.snd, r - l + 1);
	int v = V[p2.fst];
	root = merge(merge(p1.fst, p2.fst), p2.snd);
	return v;
}

int main() {
	for(int i = 0; i < N; i++) y[i] = i;
	random_shuffle(y, y + N);
	char op; int a, b;
	root = nil; vN[nil] = INT_MAX; vX[nil] = -1; mx[nil] = -1; mn[nil] = modn;
	for_tests(t, tt) {
		scanf(" %c %d", &op, &a);
		if(op == 'I') add(a);
		else if(op == 'D') rem(a);
		else {
			scanf("%d", &b);
			if(op == 'N') printf("%d\n", f(a, b, vN));
			else printf("%d\n", f(a, b, vX));
		}
	}
}

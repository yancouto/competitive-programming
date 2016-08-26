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
const int N = 7000009;

double rnd() { return double(rand()) / RAND_MAX; }

int root, tn = 1;
int val[N], L[N], R[N], sz[N], mn[N];

int calc(int u) {
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
	mn[u] = min(mn[L[u]], min(val[u], mn[R[u]]));
	return u;
}

int cp(int u) {
	if(!u) return 0;
	val[tn] = val[u];
	L[tn] = L[u];
	R[tn] = R[u];
	sz[tn] = sz[u];
	mn[tn] = mn[u];
	return tn++;
}

int merge(int l, int r) {
	if(!l || !r) return max(l, r);
	int u;
	if(rnd() * (sz[l] + sz[r]) <= sz[l]) u = cp(l), R[u] = merge(R[l], r);
	else u = cp(r), L[u] = merge(l, L[r]);
	return calc(u);
}

void split(int u, int s, int &l, int &r) {
	if(!u) return (void)(l = r = 0);
	int v = cp(u);
	if(s > sz[L[u]]) split(R[u], s - sz[L[u]] - 1, l, r), R[v] = l, l = v;
	else split(L[u], s, l, r), L[v] = r, r = v;
	calc(v);
}


int main() {
	int i, n, l, r;
	mn[0] = INT_MAX;
	root = 0;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &val[tn]); sz[tn] = 1; mn[tn] = val[tn];
		root = merge(root, tn++);
	}
	for_tests(t, tt) {
		scanf("%d %d", &l, &r);
		int t1, t2, t3;
		split(root, l, t1, t2);
		split(t2, r - l + 1, t2, t3);
		printf("%d\n", mn[t2]);
		root = merge(merge(t1, t2), t3);
	}
}

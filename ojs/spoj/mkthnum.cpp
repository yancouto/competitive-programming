// acabar
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
const int MAX = 100009;
int a[MAX], b[MAX], root[MAX], p[MAX];

int t[MAX * 25], tn, L[MAX * 25], R[MAX * 25];
int build_tree(int le, int ri) {
	if(le == ri) return tn++;
	int mi = (le + ri) / 2;
	int id = tn++;
	L[id] = build_tree(le, mi);
	R[id] = build_tree(mi + 1, ri);
	return id;
}

int update(int oid, int le, int ri, int x) {
	int id = tn++;
	if(le == ri) { t[id] = t[oid] + 1; return id; }
	L[id] = L[oid]; R[id] = R[oid];
	int mi = (le + ri) / 2;
	if(x <= mi) L[id] = update(L[oid], le, mi, x);
	else R[id] = update(R[oid], mi + 1, ri, x);
	t[id] = t[L[id]] + t[R[id]];
	return id;
}

int query(int lid, int rid, int le, int ri, int k) {
	if(le == ri) return le;
	int mi = (le + ri) / 2;
	if(t[L[rid]] - t[L[lid]] >= k) return query(L[lid], L[rid], le, mi, k);
	else return query(R[lid], R[rid], mi + 1, ri, k - (t[L[rid]] - t[L[lid]]));
}

int main() {
	int i, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		p[i] = i;
	}
	sort(p, p + n, [](int i, int j) { return a[i] < a[j]; });
	for(i = 0; i < n; i++)
		b[p[i]] = i;
	root[0] = build_tree(0, n - 1);
	for(i = 1; i <= n; i++)
		root[i] = update(root[i - 1], 0, n - 1, b[i-1]);
	int l, r, k;
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &l, &r, &k);
		printf("%d\n", a[p[query(root[l - 1], root[r], 0, n - 1, k)]]);
	}
}

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
const int N = 41234567;
int tr[N], L[N], R[N], tn;

int build(int l, int r) {
	int i = tn++;
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
}

int add(int oi, int l, int r, int id) {
	int i = tn++;
	tr[i] = tr[oi] + 1;
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = L[oi];
	R[i] = R[oi];
	if(id <= m) L[i] = add(L[i], l, m, id);
	else R[i] = add(R[i], m + 1, r, id);
	return i;
}

int find(int i, int l, int r, int k) {
	if(l == r) return l;
	int m = (l + r) / 2;
	if(tr[L[i]] >= k) return find(L[i], l, m, k);
	else return find(R[i], m + 1, r, k - tr[L[i]]);
}

const int M = 1123456;
int a[M], b[M], root[M];
vector<int> v[M];

int main() {
	int i, n, q, op, I, L, K;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b, b + n);
	int bn = unique(b, b + n) - b;
	root[0] = build(0, bn - 1);
	for(i = 0; i < n; i++) {
		a[i] = lower_bound(b, b + bn, a[i]) - b;
		v[a[i]].pb(i);
		root[i + 1] = add(root[i], 0, bn - 1, a[i]);
	}
	for(i = 0; i < q; i++) {
		scanf("%d %d", &op, &I);
		if(op) {
			if(a[I] == a[I + 1]) continue;
			(*lower_bound(v[a[I]].begin(), v[a[I]].end(), I))++;
			(*lower_bound(v[a[I+1]].begin(), v[a[I+1]].end(), I+1))--;
			root[I + 1] = add(root[I], 0, bn - 1, a[I+1]);
			swap(a[I], a[I + 1]);
		} else {
			scanf("%d %d", &L, &K);
			int num = find(root[I + 1], 0, bn - 1, K);
			if(v[num].size() < L) puts("-1");
			else printf("%d\n", v[num][L-1]);
		}
	}
}

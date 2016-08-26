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
ll tr[N << 2], lazy[N << 2];
inline int L(int i) { return i << 1; }
inline int R(int i) { return L(i) + 1; }
void build(int i, int l, int r) {
	tr[i] = lazy[i] = 0;
	if(l == r) return;
	int m = (l + r) / 2;
	build(L(i), l, m);
	build(R(i), m + 1, r);
}

void unlaze(int i, int l, int r) {
	if(lazy[i] == 0) return;
	tr[i] += ll(r - l + 1) * lazy[i];
	if(l != r) {
		lazy[L(i)] += lazy[i];
		lazy[R(i)] += lazy[i];
	}
	lazy[i] = 0;
}

void add(int i, int l, int r, int ql, int qr, int x) {
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lazy[i] = x;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(L(i), l, m, ql, qr, x);
	add(R(i), m + 1, r, ql, qr, x);
	tr[i] = tr[L(i)] + tr[R(i)];
}

vector<int> val[10009];

int main() {
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < 10004; i++) val[i].clear();
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			val[a[i]].pb(i);
		}
		scanf("%d", &m);
		for(i = 0; i < m; i++) {
			qi[i] = i;
			scanf("%d %d %d", &ql[i], &qr[i], &qm[i]);
			ql[i]--; qr[i]--;
			if(qm[i] >= 10003) qm[i] = 10003;
		}
		sort(qi, qi +  q, [](int i, int j) { return qm[i] < qm[j]; });
		int qc = 0;
		build(1, 0, n - 1);
		for(i = 1; i <= 10003; i++) {
			while(qc < q && qm[qi[qc]] == i) {
				ans[qi[qc]] = get(1, 0, n - 1, ql[qi[qc]], qr[qi[qc]]);
				qc++;
			}
			add(1, 0, n - 1, 0, n - 1, -1);
			for(j = i; j <= 10003; j += i)
				for(int k : val[j])
					add(1, 0, n - 1, k, k, );
		}
	}
}

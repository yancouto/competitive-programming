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
const int N = 9123456;

int tr[N], L[N], R[N], tn;
int n;

int g(int &u) {
	if(u != -1) return u;
	u = tn++;
	L[u] = R[u] = -1;
	tr[u] = 0;
	return u;
}

int add(int oi, int l, int r, int id) {
	int i = tn++;
	tr[i] = tr[oi] + 1;
	if(l == r) return i;
	L[i] = g(L[oi]);
	R[i] = g(R[oi]);
	int m = l + (r - l) / 2;
	if(id <= m) L[i] = add(L[i], l, m, id);
	else R[i] = add(R[i], m + 1, r, id);
	return i;
}

int find(int il, int ir, int l, int r, int k) {
	if(l == r) return l;
	int m = l + (r - l) / 2;
	if(tr[L[ir]] - tr[L[il]] >= k)
		return find(g(L[il]), g(L[ir]), l, m, k);
	else 
		return find(g(R[il]), g(R[ir]), m + 1, r, k - (tr[L[ir]] - tr[L[il]]));
}

int get(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return 0;
	if(l >= ql && r <= qr) return tr[i];
	int m = l + (r - l) / 2;
	return get(g(L[i]), l, m, ql, qr) + get(g(R[i]), m + 1, r, ql, qr);
}

int v[N], op[N], x[N], S[N], T[N], K[N], root[N];

char s[100];
int main() {
	int i, n, a, k, t = 0;
	while(scanf("%d", &n) != EOF) {
		int R = INT_MAX;
		k = tn = 0;
		root[0] = 0; tn = 1;
		L[0] = ::R[0] = -1;
		int sz = 0;
		ll t1 = 0, t2 = 0, t3 = 0;
		for(i = 0; i < n; i++) {
			scanf(" %s %d", s, &a);
			if(s[0] == 'I') {
				x[i] = a;
				v[k++] = a;
				root[sz + 1] = add(root[sz], 0, R, x[i]);
				sz++;
			} else if(s[6] == '1') {
				S[i] = a - 1;
				scanf("%d %d", &T[i], &K[i]);
				ll ans = find(root[S[i]], root[T[i]], 0, R, K[i]);
				t1 += ans;
			} else if(s[6] == '3') {
				S[i] = 0; T[i] = k;
				K[i] = a;
				ll ans = find(root[S[i]], root[T[i]], 0, R, K[i]);
				t3 += ans;
			} else {
				x[i] = a;
				ll ans = get(root[sz], 0, R, 0, x[i]);
				t2 += ans;
			}
		}
		printf("Case %d:\n%lld\n%lld\n%lld\n", ++t, t1, t2, t3);
	}
}

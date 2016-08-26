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
const int N = 2123456;

int tr[N], L[N], R[N], tn;
int n;

int build(int l, int r) {
	int i = tn++;
	tr[i] = 0;
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	return i;
}

int add(int oi, int l, int r, int id) {
	int i = tn++;
	tr[i] = tr[oi] + 1;
	if(l == r) return i;
	L[i] = L[oi];
	R[i] = R[oi];
	int m = (l + r) / 2;
	if(id <= m) L[i] = add(L[i], l, m, id);
	else R[i] = add(R[i], m + 1, r, id);
	return i;
}

int find(int il, int ir, int l, int r, int k) {
	if(l == r) return l;
	int m = (l + r) / 2;
	if(tr[L[ir]] - tr[L[il]] >= k)
		return find(L[il], L[ir], l, m, k);
	else 
		return find(R[il], R[ir], m + 1, r, k - (tr[L[ir]] - tr[L[il]]));
}

int get(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return 0;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return get(L[i], l, m, ql, qr) + get(R[i], m + 1, r, ql, qr);
}

int v[N], op[N], x[N], S[N], T[N], K[N], root[N];
enum {INS, OP1, OP2, OP3};

char s[100];
int main() {
	int i, n, a, k, t = 0;
	while(scanf("%d", &n) != EOF) {
		k = tn = 0;
		for(i = 0; i < n; i++) {
			scanf(" %s %d", s, &a);
			if(s[0] == 'I') {
				op[i] = INS;
				x[i] = a;
				v[k++] = a;
			} else if(s[6] == '1') {
				op[i] = OP1;
				S[i] = a - 1;
				scanf("%d %d", &T[i], &K[i]);
			} else if(s[6] == '3') {
				op[i] = OP3;
				S[i] = 0; T[i] = k;
				K[i] = a;
			} else {
				op[i] = OP2;
				x[i] = a;
			}
		}
		sort(v, v + k);
		for(i = 0; i < n; i++)
			if(op[i] == INS)
				x[i] = lower_bound(v, v + k, x[i]) - v;
		root[0] = build(0, k - 1);
		int sz = 0;
		ll t1 = 0, t2 = 0, t3 = 0;
		for(i = 0; i < n; i++) {
			if(op[i] == INS) {
				root[sz + 1] = add(root[sz], 0, k - 1, x[i]);
				sz++;
			} else if(op[i] == OP1 || op[i] == OP3) {
				ll ans = v[find(root[S[i]], root[T[i]], 0, k - 1, K[i])];
				if(op[i] == OP1) t1 += ans;
				else t3 += ans;
			} else {
				t2 += get(root[sz], 0, k - 1, 0, lower_bound(v, v + k, x[i]) - v);
			}
		}
		printf("Case %d:\n%lld\n%lld\n%lld\n", ++t, t1, t2, t3);
	}
}

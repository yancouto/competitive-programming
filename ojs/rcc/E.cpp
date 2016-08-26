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
const int N = 5123456;
int L[N], R[N];
ll tr[N];
int en;
int root[212345];

int add(int u, int l, int r, int x, ll v) {
	int i = ++en;
	L[i] = L[u];
	R[i] = R[u];
	tr[i] = tr[u] + v;
	if(l == r) return i;
	int m = (l + r) / 2;
	if(x <= m) L[i] = add(L[i], l, m, x, v);
	else R[i] = add(R[i], m + 1, r, x, v);
	return i;
}

ll get(int i, int l, int r, int v) {
	if(l > v) return 0;
	ll sum = 0;
	while(true) {
		if(!i) return sum;
		if(r <= v) return sum + tr[i];
		int m = (l + r) / 2;
		sum += get(R[i], m + 1, r, v);
		i = L[i]; r = m;
	}
}

int a[212345], b[212345];

int main() {
	int i, n, m, x, l, r;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]), b[i] = a[i];
	sort(b, b + n);
	int bn = unique(b, b + n) - b;
	for(i = 1; i <= n; i++)
		root[i] = add(root[i - 1], 0, bn - 1, lower_bound(b, b + bn, a[i-1]) - b, a[i-1]);
	for(i = 1; i <= m; i++) {
		scanf("%d %d", &l, &r);
		if(b[0] != 1) { puts("1"); continue; }
		ll v = 0;
		while(true) {
			int t;
			if(v + 1ll > INT_MAX) t = bn - 1;
			else t = (upper_bound(b, b + bn, int(v + 1)) - b) - 1;
			ll nv = get(root[r], 0, bn - 1, t) - get(root[l - 1], 0, bn - 1, t);
			if(nv == v) break;
			v = nv;
		}
		printf("%lld\n", v + 1ll);
	}

}

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
ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

ll fexp(ll n, ll p) {
	ll r = 1;
	for(ll i = 1; i <= p; i <<= 1) {
		if(i & p) r = mod(r * n);
		n = mod(n * n);
	}
	return r;
}

const int MAX = 100003;
ll t[MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return (i << 1) + 1; }

ll pot[MAX];
ll join(ll l, ll r, int le, int mi, int ri) {
	//printf("join(%lld, %lld) (%d, %d, %d) = %lld\n", l, r, le, mi, ri, mod(l * pot[ri - mi] + r));
	return mod(l * pot[ri - mi] + r);
}

void set_tree(int i, int le, int ri, int qi, int x) {
	if(le == ri) { t[i] = x; return; }
	int mi = (le + ri) / 2;
	if(qi <= mi) set_tree(l(i), le, mi, qi, x);
	else set_tree(r(i), mi + 1, ri, qi, x);
	t[i] = join(t[l(i)], t[r(i)], le, mi, ri);
}

ll query(int i, int le, int ri, int ql, int qr) {
	if(ri < ql || le > qr) return 0;
	if(le >= ql && ri <= qr) return t[i];
	int mi = (le + ri) / 2;
	return join(query(l(i), le, mi, ql, qr), query(r(i), mi + 1, ri, ql, qr), le, mi, ri);
}

int main() {
	int n, q, i, a, b; char op;
	while(scanf("%d %d %d %d", &b, &modn, &n, &q) != EOF && n) {
		memset(t, 0, sizeof t);
		pot[0] = 1;
		for(i = 1; i <= n; i++)
			pot[i] = mod(pot[i - 1] * b);
		for(i = 0; i < q; i++) {
			scanf(" %c %d %d", &op, &a, &b);
			if(op == 'E') set_tree(1, 0, n - 1, a - 1, b);
			else printf("%lld\n", (int) mod(fexp(pot[n - b], modn - 2) * query(1, 0, n - 1, a - 1, b - 1)));
		}
		puts("-");
	}
}

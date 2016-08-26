#include <bits/stdc++.h>
using namespace std;
#define a first
#define b second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> fr;
typedef pair<ll, ll> pll;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

bool lessf(fr p, fr q) {
	return p.a * q.b < p.b * q.a;
}

pll operator + (pll x, pll y) { return pll(x.a + y.a, x.b + y.b); }
pll operator - (pll x, pll y) { return pll(x.a - y.a, x.b - y.b); }
const int N = 112345, NS = 9123456;
int L[NS], R[NS], en;
pll tr[NS];

int add(int u, int l, int r, int x, pll v) {
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

pll get(int u, int l, int r, int v) {
	if(!u || l > v) return pll(0, 0);
	if(r <= v) return tr[u];
	int m = (l + r) / 2;
	return get(L[u], l, m, v) + get(R[u], m + 1, r, v);
}

ll a[N], b[N];
fr B[N];
int root[N];

ll brut(int l, int r, ll c, ll d) {
	ll tot = 0;
	for(int i = l; i <= r; i++)
		tot += max(0ll, c * (a[i] - a[i - 1]) - d * (b[i] - b[i - 1]));
	return tot;
}

int main() {
	srand(time(NULL));
	int i, n, l, r, bn = 0;
	ll c, d;
	scanf("%d", &n);
	for(i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
		//a[i] = rand() % 100;
	for(i = 1; i <= n; i++) {
		scanf("%lld", &b[i]);
		//b[i] = rand() % 100;
		if(b[i] > 0) B[++bn] = fr(a[i], b[i]);
	}
	//for(i = 1; i <= n; i++) printf("%lld ", a[i]); putchar('\n');
	//for(i = 1; i <= n; i++) printf("%lld ", b[i]); putchar('\n');
	//for(i = 1; i <= bn; i++) printf("%lld/%lld ", B[i].a, B[i].b); putchar('\n');
	sort(B+1, B + bn+1, lessf);
	//for(i = 1; i <= bn; i++) printf("%lld/%lld ", B[i].a, B[i].b); putchar('\n');
	root[0] = 0;
	//for(i = 1; i <= bn; i++) {
	//	root[i] = add(root[i - 1], 1, n, i, B[i]);
	//}
	for(i = 1; i <= n; i++) {
		if(b[i] == 0) root[i] = root[i - 1];
		else {
			int id = lower_bound(B+1, B + bn+1, fr(a[i], b[i]), lessf) - B;
			assert(!lessf(B[id],fr(a[i], b[i])) && !lessf(fr(a[i], b[i]), B[id]));
			root[i] = add(root[i - 1], 1, n, id, pll(a[i], b[i]));
			//printf("[%d] (%lld, %lld) \n", i, B[id].a, B[id].b);
		}
	}
	for(i = 2; i <= n; i++) a[i] += a[i - 1], b[i] += b[i - 1];
	for_tests(qn, qq) {
		//l = (rand() % n) + 1, r = (rand() % n + 1);
		//if(l > r) swap(l, r);
		//c = rand() % 10; d = rand() % 10;
		scanf("%d %d %lld %lld", &l, &r, &c, &d);
		if(c == 0) { puts("0"); fflush(stdout); continue; }
		ll sum = (a[r] - a[l - 1]) * c - (b[r] - b[l - 1]) * d;
		if(d == 0) { printf("%lld\n", sum); fflush(stdout); continue; }
		pll o(0, 0);
		if(bn && !lessf(fr(d, c), B[1])) {
			int id = (lower_bound(B+1, B+1+bn, fr(d, c), lessf) - B) - 1;
			//printf("id %d out of %d\n", id, bn);
			//printf("(%lld, %lld) - (%lld, %lld)\n", get(root[r], 1, n, id).a, get(root[r], 1, n, id).b, get(root[l-1], 1, n, id).a, get(root[l-1], 1, n, id).b);
			o = get(root[r], 1, n, id) - get(root[l - 1], 1, n, id);
			//printf("x %lld %lld\n", x.a, x.b);
		}
		//printf("o %lld %lld\n", o.a, o.b);
		sum -= o.a * c;
		sum += o.b * d;
		printf("%lld\n", sum);
		//printf("%lld\n", brut(l, r, c, d));
		//assert(sum == brut(l, r, c, d));
		fflush(stdout);
	}
}

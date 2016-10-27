#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const ll B = 212345;

const int N = 212345;

ll tr[4*N], lm[4 * N], ls[4 * N];

void unlaze(int i, int l, int r) {
	if(lm[i] == 1 && ls[i] == 0) return;
	if(l != r)
		for(int s = 2 * i; s <= 2 * i + 1; s++) {
			ll c = lm[s], d = ls[s];
			lm[s] = mod(c * lm[i]);
			ls[s] = mod(lm[i] * d + ls[i]);
		}
	else
		tr[i] = mod(lm[i] * tr[i] + ls[i]);
	lm[i] = 1; ls[i] = 0;
}

void upd(int i, int l, int r, int ql, int qr, ll mu, ll su) {
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lm[i] = mu; ls[i] = su;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	upd(2 * i, l, m, ql, qr, mu, su);
	upd(2 * i + 1, m + 1, r, ql, qr, mu, su);
}

ll get(int i, int l, int r, int x) {
	unlaze(i, l, r);
	if(l == r) return tr[i];
	int m = (l + r) / 2;
	if(x <= m) return get(2 * i, l, m, x);
	else return get(2 * i + 1, m + 1, r, x);
}

int main() {
	int i, n, k, l, r, x;
	for(i = 0; i < 4 * N; i++) lm[i] = 1;
	scanf("%d %d", &n, &k);
	for_tests(tn, tt) {
		scanf("%d %d %d", &l, &r, &x); l--; r--;
		upd(1, 0, n - 1, l, r, B, x);
	}
	ll num = 0;
	for(i = 1; i <= k; i++)
		num = mod(num * B + i);
	int tot = 0;
	for(i = 0; i < n; i++)
		if(get(1, 0, n - 1, i) == num)
			tot++;
	printf("%d\n", tot);
}

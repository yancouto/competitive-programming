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
ll h[N], acc[N], l1[N][20], l2[N][20];

ll mx_d(ll l[N][20], int i, int j) {
	if(i > j) return LLONG_MIN;
	int e = 31 - __builtin_clz(j - i + 1);
	return max(l[i][e], l[j - (1 << e) + 1][e]);
}
int n;

ll bl(ll i, ll x) {
	if(mx_d(l1, 1, i - 1) < x - i) return LLONG_MAX;
	if(mx_d(l2, i + 1, n) < x + i) return LLONG_MAX;
	ll tot = x - h[i];
	ll l = 1, r = i - 1;
	while(l < r) {
		ll m = (l + r + 1) / 2;
		if(mx_d(l1, m, i) >= x - i) l = m;
		else r = m - 1;
	}
	ll st = x - (i - l) + 1;
	if(l != i - 1) tot += ((st + x - 1) * (x - st)) / 2 - (acc[i - 1] - acc[l]);
	l = i + 1, r = n;
	while(l < r) {
		ll m = (l + r) / 2;
		if(mx_d(l2, i, m) >= x + i) r = m;
		else l = m + 1;
	}
	st = x - (l - i) + 1;
	if(l != i + 1) tot += ((st + x - 1) * (x - st)) / 2 - (acc[l - 1] - acc[i]);
	return tot;
}

int main() {
	freopen("landscape.in", "r", stdin);
	freopen("landscape.out", "w", stdout);
	int i, j;
	ll b;
	scanf("%d %I64d", &n, &b);
	for(i = 1; i <= n; i++) {
		scanf("%I64d", &h[i]);
		acc[i] = acc[i - 1] + h[i];
		l1[i][0] = h[i] - i;
		l2[i][0] = h[i] + i;
	}
	for(j = 1; j < 20; j++)
		for(i = 0; i <= n; i++)
			l1[i][j] = max(l1[i][j - 1], l1[min(i + (1 << (j - 1)), n+1)][j - 1]),
			l2[i][j] = max(l2[i][j - 1], l2[min(i + (1 << (j - 1)), n+1)][j - 1]);
	ll best = 0;
	for(i = 1; i <= n; i++) {
		ll l = 0, r = 2200000000;
		while(l < r) {
			ll m = (l + r + 1) / 2;
			if(bl(i, h[i] + m) <= b) l = m;
			else r = m - 1;
		}
		best = max(best, l + h[i]);
	}
	printf("%I64d\n", best);
}

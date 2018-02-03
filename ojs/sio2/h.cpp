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

int tr[2003][2001 << 2];

void set_(int o, int i, int l, int r, int p, ll x) {
	//if(i == 1) printf("[%d] (%d) = %lld\n", o, p, x);
	if(l == r) return (void) (tr[o][i] = x);
	int m = (l + r) / 2;
	if(p <= m) set_(o, 2 * i, l, m, p, x);
	else set_(o, 2 * i + 1, m + 1, r, p, x);
	tr[o][i] = min(tr[o][2 * i], tr[o][2 * i + 1]);
}

ll get(int o, int i, int l, int r, int ql, int qr) {
	//if(i == 1) printf("[%d] (%d, %d)\n", o, ql, qr);
	if(l > qr || r < ql) return LLONG_MAX;
	if(l >= ql && r <= qr) return tr[o][i];
	int m = (l + r) / 2;
	return min(get(o, 2 * i, l, m, ql, qr), get(o, 2 * i + 1, m + 1, r, ql, qr));
}

ll get_mn1(int l, int m, int r) {
	//printf("get_mn1(%d, %d, %d) = %lld\n", l, m, r, get(r, 1, 0, 1999, l + 1, m + 1));
	return get(r, 1, 0, 1999, l, m);
}

ll get_mn2(int l, int m, int r) {
	//printf("get_mn2(%d, %d, %d) = %lld\n", l, m, r, get(2001 + l, 1, 0, 1999, m - 1, r - 1));
	return get(l, 1, 0, 1999, m, r);
}

int a[2123];
ll dp[2123][2123];
int n;

void finish(int l, int r) {
	//if(l) {
		//printf("r (%d, %d) = %lld + %d\n", l, r, dp[l][r], a[l - 1]);
		set_(r, 1, 0, 1999, l - 1, dp[l][r] + a[l - 1]);
	//}
	//if(r != n - 1) {
		//printf("l (%d, %d) = %lld + %d\n", l, r, dp[l][r], a[r + 1]);
		set_(l, 1, 0, 1999, r + 1, dp[l][r] + a[r + 1]);
	//}
}

void calc(int l, int r) {
	//printf("calc(%d, %d)\n", l, r);
	int fst;
	{
		int ql = l, qr = r;
		while(ql < qr) {
			int m = (ql + qr) / 2;
			if(dp[l][m - 1] < dp[m + 1][r])
				ql = m + 1;
			else
				qr = m;
		}
		fst = ql;
	}
	//printf("fst %d\n", fst);
	dp[l][r] = get_mn1(l, fst - 1, r);
	dp[l][r] = min(dp[l][r], get_mn2(l, fst, r));
	//printf("= %lld\n", dp[l][r]);
}

int main() {
	int i;
	scanf("%d", &n);
	for(i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(i = 1; i <= n; i++) {
		dp[i][i] = a[i];
		finish(i, i);
	}
	for(int l = 2; l <= n; l++)
		for(int i = 1; i + l - 1 <= n; i++) {
			calc(i, i + l - 1);
			finish(i, i + l - 1);
		}
	printf("%lld\n", dp[1][n]);
}

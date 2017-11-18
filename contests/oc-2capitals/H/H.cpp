#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 1e2+7;
const ll MOD = 1e9+7;

int n, m, k;
int v[N];

ll memo[N][N];
ll f[(1<<18)];

ll pd (int n, int k) {
	if (n < k) return 0;
	if (k == 0) return 1;

	ll & me = memo[n][k];
	if (me != -1) return me;
	me = (pd(n-1,k)+pd(n-1,k-1))%MOD;
	return me;
}

int conv (int mask, int sub) {
	int res = 0;
	for (int i = 0; i < n; i++) {
		int j = (mask&(-mask));
		if (sub&(1<<i))
			res += j;
		mask -= j;
	}
	return res;
}

int main() {
	memset(memo, -1, sizeof memo);
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 0; i < m; i++) {
		int s;
		scanf("%d", &s);
		for (int j = 0; j < s; j++) {
			int a;
			scanf("%d", &a);
			v[a-1] |= (1<<i);
		}
	}

	ll res = 0;
	for (int mask = 1; mask < (1<<m); mask++) {
		ll qt = 0;
		
		for (int i = 0; i < n; i++)
			f[v[i]&mask]++;

		for (int i = 0; i < n; i++) {
			int cur = (v[i]&mask);
			qt = (qt + ((pd(f[cur],k)*pd(f[mask-cur],k))%MOD))%MOD;
			qt = (qt + ((pd(f[mask-cur],k)*pd(f[cur],k))%MOD))%MOD;
			f[cur] = f[mask-cur] = 0;
		}

		if ((__builtin_popcount(mask)&1) == 0)
			qt = (MOD - qt);
		res = (res + qt)%MOD;
	}
	printf("%lld\n", res);
}

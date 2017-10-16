#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 102;
const int H = 2e4+7;

int n, m, k;
int c[N][3];
vector<pii> v[H];

ll sq (ll x) {
	return x*x;
}

ll sqr (ll x) {
	ll lo = 0, hi = x;
	while (lo < hi) {
		ll md = (lo+hi+1)/2;
		if (sq(md) > x)
			hi = md - 1;
		else
			lo = md;
	}
	return lo;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("circles.in", "r", stdin);
	freopen("circles.out", "w", stdout);
#endif

	scanf("%d %d %d", &m, &n, &k);

	for (int i = 0; i < k; i++) {
		scanf("%d %d %d", &c[i][1], &c[i][0], &c[i][2]);

		for (int l = max(0, c[i][0] - c[i][2]); l <= c[i][0] + c[i][2] && l < n; l++) {
			ll dx = sqr(sq(c[i][2]) - sq(l - c[i][0]));

			v[l].pb(pii(c[i][1] - dx, 1));
			v[l].pb(pii(c[i][1] + dx + 1, -1));
		}
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		sort(v[i].begin(), v[i].end());

		int qt = 0;
		int p = 0;
		for (int j = 0; j < m; j++) {
			while (p < v[i].size() && v[i][p].first <= j)
				qt += v[i][p++].second;

			if (qt == 0)
				res++;
		}
	}
	printf("%d\n", res);
}


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1e5+7;

int n, m, k;
pii v[N];
bitset<N> s;

int main () {
	scanf("%d %d %d", &n, &m, &k);

	for (ll i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		a--;
		v[a].first = max(v[a].first, i+1);
		v[a].second++;
	}

	sort(v, v+m);

	ll mn = ll(n)*ll(n) + 1;
	s[0] = 1;
	
	for (int i = 0; i < m; i++) {
		for (int j = k; j >= 0; j--) {
			if (!s[j]) continue;
			ll a = j + v[i].second;
			ll b = n - a;
			if (a <= k && b <= k) {
				mn = min(mn, a * v[i].first + b * n);
			}
			if (a <= k)
				s[a] = 1;
		}
	}

	if (mn == ll(n)*ll(n) + 1)
		mn = -1;
	printf("%lld\n", mn);
}

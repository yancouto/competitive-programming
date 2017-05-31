#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a[112345];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%lld", &a[i]);
	ll all = accumulate(a, a + n, 0ll);
	ll beg = 0;
	ll mx = 0;
	for(i = 0; i < n - 1; i++) {
		beg += a[i];
		all -= a[i];
		mx = max(mx, beg * all);
	}
	printf("%lld\n", mx);

}

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
typedef pair<int, int> pii;
#define pb push_back

ll c[112];
int t; ll s;
bool ok(ll g) {
	ll sum = 0;
	for(int i = 0; i < t; i++)
		sum += min(c[i], g);
	return (sum / g) >= s;

}

int main() {
	int i, q;
	scanf("%d", &q);
	while(q--) {
		scanf("%d %llu", &t, &s);
		for(i = 0; i < t; i++) scanf("%llu", &c[i]);
		ll l = 0, r = 6.01e18;
		while(l < r) {
			ll m = (l + r + 1ll) / 2;
			if(ok(m)) l = m;
			else r = m - 1;
		}
		printf("%llu\n", l);
	}
}

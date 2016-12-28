#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 11234;
int x[N], y[N], t, seen[N], n; ll p;

inline ll sqr(ll x) { return x * x; }

int go(int i) {
	if(seen[i] == t) return 0;
	seen[i] = t;
	int r = 1;
	for(int j = 0; j < n; j++)
		if(sqr(x[i] - x[j]) + sqr(y[i] - y[j]) <= p)
			r += go(j);
	return r;
}

int main() {
	freopen("moocast.in", "r", stdin);
	freopen("moocast.out", "w", stdout);
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);
	ll l = 0, r = 1500000000;
	while(l < r) {
		ll m = (l + r) / 2;
		p = m;
		t++;
		if(go(0) == n) r = m;
		else l = m + 1;
	}
	printf("%lld\n", l);
}

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;


const int N = 512345;
ll x[N], r[N];

int main() {
	int n, i;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%lld %lld", &x[i], &r[i]);
	ll cx = x[0];
	for(i = 0; i < n; i++) {
		if(cx >= x[i]) cx = max(cx, x[i] + r[i]);
		else { puts("-1"); return 0; }
	}
	cx = x[n - 1];
	for(i = n - 1; i >= 0; i--) {
		if(cx <= x[i]) cx = min(cx, x[i] - r[i]);
		else { puts("-1"); return 0; }
	}
	printf("%lld\n", 3ll * ll(x[n - 1] - x[0]));
}

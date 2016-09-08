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

int main() {
	int r, y, b;
	while(scanf("%d %d %d", &r, &y, &b) != EOF) {
		ll ans = 0;
		int pr = 0;
		if(r == 0 && y == 0 && b == 0) { puts("0"); continue; }
		if(r) r--, ans += pr, pr++;
		if(y) y--, ans += pr, pr++;
		if(b) b--, ans += pr, pr++;
		if(r) r--, ans += pr, pr++;
		if(y) y--, ans += pr, pr++;
		if(b) b--, ans += pr, pr++;
		ans += ll(ll(r) + ll(y) + ll(b)) * ll(pr);
		printf("%lld\n", ans);
	}
}

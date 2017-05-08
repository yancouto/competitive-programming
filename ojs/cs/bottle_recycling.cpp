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
	int n, k;
	scanf("%d %d", &n, &k);
	ll tot = n;
	while(n >= k) {
		tot += n / k;
		n = (n % k) + (n / k);
	}
	printf("%lld\n", tot);
}

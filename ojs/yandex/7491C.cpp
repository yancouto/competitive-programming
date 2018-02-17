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
	int n;
	scanf("%d", &n);
	ll ans = 1;
	for(int i = 0; i < (n - 1) * (n - 1); i++)
		ans = mod(ans * n);
	printf("%lld\n", ans);
}

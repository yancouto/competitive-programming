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

ll n;

int main () {
	scanf(" %lld", &n);
	if (n == 1) {
		printf("YES\n");
		return 0;
	} else  if (n == 4) {
		printf("NO\n");
		return 0;
	}

	for (ll i = 2; i*i <= n; i++) {
		if (n%i == 0) {
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
}

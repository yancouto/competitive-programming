#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

ll n;
ll ts;

int main() {
	int i, j;
	scanf("%lld", &ts);

	while (ts--) {
		scanf("%lld", &n);

		printf("%lld\n", (n+1)/2 + (n+1)/2 - (((n-1)/3)+1)/2);
	}
}

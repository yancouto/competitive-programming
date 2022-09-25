
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
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif


char a[112345];

ll solve() {
	int n, s;
	scanf("%d %d", &n, &s);
	if(n == 1) return s;
	int m = (n / 2) + 1;
	return s / m;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) printf("%lld\n", solve());
}

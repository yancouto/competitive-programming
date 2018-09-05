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

int n;
char s[1123];

ll solve(int i) {
	if(i == n) return 0;
	if(s[i] == '0') return solve(i + 1);
	ll half = (1ll << (n - i - 1));
	return half + (half - 1 - solve(i + 1));
}

int main() {
	int i, j;
	scanf("%d %s", &n, s);
	ll p = solve(0);
	scanf("%s", s);
	ll p2 = solve(0);
	printf("%lld\n", abs(p - p2) - 1ll);
}

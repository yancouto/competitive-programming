#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

typedef long double ld;

const ld pi = real(acos<ld>(-1)), eps = 1e-16;

int main() {
	ll a, b, R;
	scanf("%lld %lld %lld", &a, &b, &R);
	int val = 0;
	ll l = 3, r = 1e18;
	while(l < r) {
		ll m = (l + r) / 2;
		if(R >= (a + R) * real(sin<ld>(pi / m)) - eps) r = m;
		else l = m + 1;
	}
	ll A = l;
	l = 3; r = 1e18;
	while(l < r) {
		ll m = (l + r + 1) / 2;
		if(R <= (b + R) * real(sin<ld>(pi / m)) + eps) l = m;
		else r = m - 1;
	}
	ll B = l;
	printf("%lld\n", B - A + 1);
}

#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int a[112345];

int main() {
	int i, j, n, k; ll tot = 0;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		tot += a[i];
	}
	int l = (tot + n - 1) / n, r = 1e9 + 2;
	while(l < r) {
		int m = (l + r) / 2;
		tot = 0;
		for(i = 0; i < n; i++) tot += max(0, a[i] - m);
		if(tot <= k) r = m;
		else l = m + 1;
	}
	printf("%d\n", l);
}

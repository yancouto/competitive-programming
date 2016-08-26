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

int a[100];
int main() {
	int i, j, o = 0, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d ", &a[i]);
		if(i < n - 1) o |= ((getchar() == '+') << i);
	}
	n--;
	int mn = 1000;
	for(i = 0; i < (1 << n); i++) {
		int v = a[0];
		for(j = 0; j < n; j++)
			if((i >> j) & 1) v += a[j + 1];
			else v -= a[j + 1];
		if(v == 0) mn = min(mn, __builtin_popcount(o ^ i));
	}
	if(mn == 1000) puts("-1");
	else printf("%d\n", mn);
}

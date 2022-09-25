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
	scanf(" %s", a);
	int i = 0, j = strlen(a) - 1;
	while(a[i] && a[i] == '1') i++;
	while(j >= 0 && a[j] == '1') j--;
	if (i > j) return 0;
	for(int k = i; k <= j; k++)
		if (a[k] == '1')
			return 2;
	return 1;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) printf("%lld\n", solve());
}

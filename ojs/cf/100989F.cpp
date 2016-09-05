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

int a[112345], ct[112345];

int main() {
	int i, j, n, m, q, x, y;
	scanf("%d %d %d", &n, &m, &q);
	int cur = m;
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if(ct[a[i]]++ == 0) cur--;
	}
	for(i = 0; i < q; i++) {
		scanf("%d %d", &x, &y); x--;
		if(--ct[a[x]] == 0) cur++;
		if(ct[a[x] = y]++ == 0) cur--;
		printf("%d\n", cur);
	}

}

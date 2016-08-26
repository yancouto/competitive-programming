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

int main() {
	int i, j, n, m, t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		int cur = 1, tot = 0;
		while(n > 0 && cur < m) {
			n -= cur;
			cur *= 2;
			tot++;
		}
		if(n < 0) n = 0;
		tot += ((n + m - 1) / m);
		printf("%d\n", tot);
	}
}

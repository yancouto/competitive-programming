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
	int i, j, n, t, x;
	scanf("%d", &t);
	while(t--) {
		vector<int> a, b;
		for(i = 0; i < 3; i++) scanf("%d", &x), a.pb(x);
		for(i = 0; i < 3; i++) scanf("%d", &x), b.pb(x);
		if(a < b) puts("Player1");
		else if(a > b) puts("Player2");
		else puts("Tie");
	}
}

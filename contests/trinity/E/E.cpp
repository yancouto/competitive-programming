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

int lg(int x) {
	return 31 - __builtin_clz(x);
}

int main() {
	int i, j, a, b;
	scanf("%d %d", &a, &b);
	if(a > b) swap(a, b);
	int nb = b;
	while(nb > a) nb >>= 1;
	if(nb == a) { puts("-1"); return 0; }
	vector<int> ans;
	ans.pb(a);
	ans.pb(b);
	while(a != b) {
		if(lg(a) < lg(b)) swap(a, b);
		int pa = a;
		a >>= 1;
		if(a == b) break;
		if(2 * a != pa && 2 * a != b) ans.pb(2 * a);
		if(2 * a + 1 != pa && 2 * a + 1 != b) ans.pb(2 * a + 1);
	}
	while(a > 1) {
		int pa = a;
		a >>= 1;
		if(2 * a != pa) ans.pb(2 * a);
		else ans.pb(2 * a + 1);
	}
	sort(ans.begin(), ans.end());
	for(int x : ans) printf("%d ", x);
	printf("\n");
}

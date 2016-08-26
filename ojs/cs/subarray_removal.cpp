#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int a[112345];
ll memo[112345][2][2][2];
int n;
ll solve(int i, bool ch, bool rm, bool can) {
	if(i == n) return 0;
	ll &r = memo[i][ch][rm][can];
	if(r != -1) return r;
	r = 0;
	if(ch) {
		r = max(r, ll(a[i]) + solve(i + 1, true, false, can));
		if(rm) r = max(r, solve(i + 1, true, true, false));
		if(can) r = max(r, solve(i + 1, true, true, false));
	} else {
		r = max(r, ll(a[i]) + solve(i + 1, true, false, true));
		r = max(r, solve(i + 1, false, false, true));
	}
	return r;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	if(*max_element(a, a + n) < 0) { printf("%d\n", *max_element(a, a + n)); return 0; }
	if(*min_element(a, a + n) >= 0) { printf("%lld\n", accumulate(a, a + n, 0ll) - *min_element(a, a + n)); return 0; }
	memset(memo, -1, sizeof memo);
	printf("%lld\n", solve(0, 0, 0, 1));
}

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

char s[1000009];
ll memo[1000003][3][2];
ll solve(int i, int sum, bool sel) {
	if(!s[i]) return sel && !sum;
	ll &r = memo[i][sum][sel];
	if(r != -1) return r;
	r = sel && !sum;
	if(!sel) r += solve(i + 1, 0, false);
	if(isdigit(s[i])) r += solve(i + 1, (sum + s[i] - '0') % 3, true);
	return r;
}

int main() {
	scanf("%s", s);
	memset(memo, -1, sizeof memo);
	printf("%lld\n", solve(0, 0, false));
}

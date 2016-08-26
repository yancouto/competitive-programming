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

ull mx(ull a, ull b) { return max(a, b); }
ull mn(ull a, ull b) { return min(a, b); }

char s[109];
int seen[109][109], t;
ull memo[109][109], lm;
auto fun = mx;
ull solve(int l, int r) {
	if(l == r) return s[l] - '0';
	ull &ans = memo[l][r];
	if(seen[l][r] == t) return ans;
	seen[l][r] = t;
	ans = lm;
	for(int i = l + 1; i <= r; i += 2) {
		ull L = solve(l, i - 1), R = solve(i + 1, r);
		if(s[i] == '+') ans = fun(ans, L + R);
		else ans = fun(ans, L * R);
	}
	return ans;
}

int main() {
	for_tests(tn, tt) {
		scanf("%s", s);
		lm = 0; fun = mx; t++;
		printf("%llu ", solve(0, strlen(s) - 1));
		lm = ULLONG_MAX; fun = mn; t++;
		printf(" %llu\n", solve(0, strlen(s) - 1));
	}
}

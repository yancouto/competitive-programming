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
ll mxl(ll a, ll b) { return max(a, b); }
ll mnl(ll a, ll b) { return min(a, b); }
int a[500]; char op[500];
ll memo[500][500][2];
int seen[500][500][2], tempo;
ll solve(int l, int r, bool mx) {
	if(l == r) return a[l];
	ll &ret = memo[l][r][mx];
	if(seen[l][r][mx] == tempo) return ret;
	seen[l][r][mx] = tempo;
	ret = mx? LLONG_MIN : LLONG_MAX;
	ll (*fun)(ll, ll) = mx? mxl : mnl;
	for(int i = l; i < r; i++) {
		ll xl1 = solve(l, i, false);
		ll xr1 = solve(i + 1, r, false);
		ll xl2 = solve(l, i, true);
		ll xr2 = solve(i + 1, r, true);
		if(op[i] == '?' || op[i] == '+')
			ret = fun(ret, fun(xl1 + xr1, xl2 + xr2));
		if(op[i] == '?' || op[i] == '-')
			ret = fun(ret, fun(xl1 - xr2, xl2 - xr1));
		if(op[i] == '?' || op[i] == '*')
			ret = fun(ret, fun(fun(xl1 * xr1, xl2 * xr2), fun(xl1 * xr2, xl2 * xr1)));
	}
	return ret;
}

char s[10000];
int main() {
	int n, i;
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++)
			scanf("%d %c", &a[i], &op[i]);
		for(i = n; i < 2*n; i++)
			a[i] = a[i - n], op[i] = op[i - n];
		int sn = 0;
		tempo++;
		for(i = 0; i < n; i++) {
			ll x = solve(i, i + n - 1, false);
			sprintf(s + sn, "%lld", abs(x));
			sn += strlen(s + sn);
			x = solve(i, i + n - 1, true);
			sprintf(s + sn, "%lld", abs(x));
			sn += strlen(s + sn);
		}
		printf("%s\n", s);
	}
}

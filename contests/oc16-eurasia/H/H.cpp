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

int memo[2][112345][2];
int& dp(int n, int m, int k) { return memo[n&1][m][k]; }
pii a[112345];
int main() {
	int i, m, h, n, s;
	scanf("%d %d", &n, &s);
	for(i = 0; i < n; i++)
		scanf("%d %d", &a[i].fst, &a[i].snd);
	sort(a, a + n);
	for(i = 1; i <= s; i++)
		dp(n, i, 0) = dp(n, i, 1) = -1e9;
	for(i = n - 1; i >= 0; i--)
		for(m = s; m >= 0; m--)
			for(h = 0; h < 2; h++) {
				dp(i, m, h) = dp(i + 1, m, h && a[i+1].fst == a[i].fst);
				if(m >= a[i].snd) dp(i, m, h) = max(dp(i, m, h), !h + dp(i + 1, m - a[i].snd, (a[i+1].fst == a[i].fst)));
			}
	if(dp(0, s, 0) <= 0) puts("Impossible");
	else printf("%d\n", dp(0, s, 0));
}

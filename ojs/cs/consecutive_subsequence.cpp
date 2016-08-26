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

int a[112345], val[1123456];
int dp0[112345], dp1[112345];
int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	for(i = n - 1; i >= 0; i--) {
		if(val[a[i] + 1]) dp0[i] = dp0[val[a[i] + 1]] + 1;
		else dp0[i] = 1;
		dp1[i] = dp0[i] + 1;
		if(val[a[i] + 2]) dp1[i] = max(dp1[i], dp0[val[a[i] + 2]] + 2);
		if(val[a[i] + 1]) dp1[i] = max(dp1[i], dp1[val[a[i] + 1]] + 1);
		val[a[i]] = i;
	}
	printf("%d\n", max(*max_element(dp0, dp0 + n) + 1, *max_element(dp1, dp1 + n)));
}

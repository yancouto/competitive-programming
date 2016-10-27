#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 212345;
int f[N], bad[N];
ll ans[N];

int main() {
	int n, c, i;
	scanf("%d %d", &n, &c);
	ll tot = c;
	ans[1] = c;
	bad[0] = 1;
	for(i = 2; i <= n; i++) {
		scanf("%d", &f[i]);
		bad[i - 1] = bad[f[i - 1]] + (f[i] == 0);
		//printf("bad[%d] = %d\n", i-1, bad[i-1]);
		if(f[i] > 0) ans[i] = 1;
		else ans[i] = c - bad[f[i - 1]];
		//printf("ans[%d] = %lld\n", i, ans[i]);
		tot = mod(tot * ans[i]);
	}
	printf("%lld\n", tot);
}

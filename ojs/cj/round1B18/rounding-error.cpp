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

int round(int a, int b) {
	//return floor((a * 100.0L) / b + 0.5L);
	int x = (a * 1000) / b;
	if((x % 10) >= 5) x = int(x / 10) * 10 + 10;
	else x = int(x / 10) * 10;
	return x / 10;
}

const int N = 212345;
int a[N];

int n;
int memo[212][112];
int dp(int i, int left) {
	if(i == 2 * n) return left == 0? 0 : -100000;
	int &r = memo[i][left];
	if(r != -1) return r;
	r = -100000;
	for(int l = a[i]; l <= left; l++)
		r = max(r, round(l, n) + dp(i + 1, left - l));
	return r;
}

int main() {
	for_tests(tn, tt) {
		int i, l;
		scanf("%d %d", &n, &l);
		for(i = 0; i < l; i++)
			scanf("%d", &a[i]);
		for(i = l; i < 2 * n; i++) a[i] = 0;
		printf("Case #%d: ", tt);
		if(n <= 105) {
			memset(memo, -1, sizeof memo);
			printf("%d\n", dp(0, n));
		} else {
			vector<int> all;
			int y;
			int ans = 0;
			for(i = 0; i < l; i++) {
				for(y = 1; round(a[i], n) == round(a[i] + y, n); y++);
				assert(round(a[i], n) + 1 == round(a[i] + y, n));
				all.pb(y);
				ans += round(a[i], n);
			}
			for(y = 1; round(y, n) == 0; y++);
			assert(round(y, n) == 1);
			for(i = 0; i < n; i++) all.pb(y);
			int cur = accumulate(a, a + l, 0);
			sort(all.begin(), all.end());
			for(int x : all) {
				if(cur + x <= n) {
					cur += x;
					ans++;
				} else break;
			}
			printf("%d\n", ans);
		}
	}
}

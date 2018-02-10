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

int ans[1123456];

int main() {
	int i;
	for_tests(tn, tt) {
		ll x, n;
		scanf("%lld %lld", &x, &n);
		ll on = n;
		ll tgt = (n * (n + 1ll)) / 2ll - x;
		if(tgt & 1) { puts("impossible"); continue; }
		tgt /= 2;
		memset(ans, 0, (n + 3) * sizeof(int));
		ans[x] = 2;
		if(x >= 3) {
			for(ll i = n; i > 0; i--)
				if(i != x && i <= tgt) {
					tgt -= i;
					ans[i] = 1;
				}
			assert(tgt == 0);
		} else if(x == 1) {
			int cl = (n - 1) % 4;
			if(cl >= 2) { puts("impossible"); continue; }
			if(cl == 0) {
				if(n < 5) { puts("impossible"); continue; }
				while(n > 5) {
					ans[n] = ans[n - 3] = 1;
					n -= 4;
				}
				ans[5] = ans[2] = 1;
			} else if(cl == 1) {
				if(n < 6) { puts("impossible"); continue; }
				while(n > 6) {
					ans[n] = ans[n - 3] = 1;
					n -= 4;
				}
				ans[6] = ans[4] = 1;
			}
		} else if(x == 2) {
			int cl = (n - 1) % 4;
			if(cl <= 1) { puts("impossible"); continue; }
			if(cl == 2) {
				if(n < 7) { puts("impossible"); continue; }
				while(n > 7) {
					ans[n] = ans[n - 3] = 1;
					n -= 4;
				}
				ans[7] = ans[6] = 1;
			} else if(cl == 3) {
				if(n < 4) { puts("impossible"); continue; }
				while(n > 4) {
					ans[n] = ans[n - 3] = 1;
					n -= 4;
				}
				ans[4] = 1;
			}
		}
		ll X = 0, Y = 0;
		for(i = 1; i <= on; i++) {
			if(ans[i] == 0) X += i;
			else if(ans[i] == 1) Y += i;
			printf("%d", ans[i]);
		}
		assert(X == Y);
		putchar('\n');
	}
}

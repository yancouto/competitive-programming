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

const int N = (1 << 17);
int a[N], has[N], ct[N], cc[N];

int main() {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		ct[a[i]]++;
		cc[a[i]]++;
	}
	for(i = (1 << 17) - 2; i >= 0; i--) {
		int fst = (1 << __builtin_ctz(~i));
		int bk = (i + 1) | i;
		ct[i] += ct[bk];
		if(bk == ((1 << 17) - 1)) continue;
		for(int bm = ((bk + 1) | bk); bm != (1 << 17) - 1; bm = ((bm + 1) | bk)) {
			ct[i] += cc[bm ^ fst];
		}
	}
	int mx = *max_element(a, a + n);
	for(i = (1 << 17) - 1; i > 0; i--) {
		if(!(i & (i - 1))) continue;
		int bk = (i - 1) & i, bm;
		for(bm = bk; bm; bm = ((bm - 1) & bk)) {
			if(ct[bm] && ct[i ^ bm]) break;
		}
		if(bm) break;
	}
	mx = max(mx, i);
	ll tot = 0;
	for(i = 0; i < n; i++) {
		if(a[i] == mx) tot--;
		tot += ct[mx ^ (mx & a[i])];
	}
	printf("%d %lld\n", mx, tot / 2);
}

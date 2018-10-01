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

const int N = 19;
int x[N], y[N], a[N];

int main() {
	for_tests(tn, tt) {
		int i, j, n, m;
		scanf("%d %d", &n, &m);
		int z = (m / 2);
		for(i = 0; i < n; i++) {
			int x = 0, y = 0; char c;
			for(j = 0; j < z; j++) {
				scanf(" %c", &c);
				x = (x << 1) | (c == '0');
			}
			for(j = z; j < m; j++) {
				scanf(" %c", &c);
				y = (y << 1) | (c == '0');
			}
			::x[i] = x; ::y[i] = y;
			scanf("%d", &a[i]);
		}
		map<string, int> ocs;
		map<string, int> one;
		for(i = 0; i < (1 << z); i++) {
			string co;
			for(j = 0; j < n; j++)
				co.pb(__builtin_popcount(i ^ x[j]));
			ocs[co]++;
			one[co] = i;
		}
		ll ans = 0;
		int sol = 0;
		for(i = 0; i < (1 << (m - z)); i++) {
			string co;
			for(j = 0; j < n; j++)
				co.pb(a[j] - __builtin_popcount(i ^ y[j]));
			ans += ocs[co];
			if(ocs[co])
				sol = (one[co] << (m - z)) | i;
		}
		if(ans == 1) {
			for(i = m - 1; i >= 0; i--) putchar('0' + ((sol >> i) & 1));
			putchar('\n');
		} else
			printf("%lld solutions\n", ans);
	}
}

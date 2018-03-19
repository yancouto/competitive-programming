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

const int N = 112345;

int acc[2][N], a[N], mrk[N];

int main() {
	int i, j, n, m, k;
	for_tests(tn, tt) {
		scanf("%d %d %d", &n, &m, &k);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		for(i = 0; i < n; i++) acc[0][i] = acc[1][i] = 0;
		for(j = 0; j < m; j++) {
			char c; int l, r;
			scanf(" %c %d %d", &c, &l, &r); l--; r--;
			int t = (c == 'I');
			acc[t][l]++;
			acc[t][r]--;
		}
		for(i = 1; i < n; i++) {
			acc[0][i] += acc[0][i - 1];
			acc[1][i] += acc[1][i - 1];
		}
		for(i = 0; i < n; i++) acc[0][i] = (acc[0][i] > 0), acc[1][i] = (acc[1][i] > 0);
		for(i = 0; i < n - 1; i++)
			if(acc[0][i] && acc[1][i])
				break;
		if(i < n - 1) { puts("0"); continue; }
		ll ans = 1;
		for(i = 0; i < n - 1; i++)
			if(acc[1][i] && a[i] != -1) {
				if(a[i + 1] != -1 && a[i + 1] != a[i] + 1) ans = 0;
				a[i + 1] = a[i] + 1;
				if(a[i + 1] > k) ans = 0;
			} else if(acc[0][i] && a[i] != -1) {
				if(a[i + 1] != -1 && a[i + 1] != a[i] - 1) ans = 0;
				a[i + 1] = a[i] - 1;
				if(a[i + 1] <= 0) ans = 0;
			}
		for(i = n - 1; i > 0; i--)
			if(acc[1][i - 1] && a[i] != -1) {
				if(a[i - 1] != -1 && a[i - 1] != a[i] - 1) ans = 0;
				a[i - 1] = a[i] - 1;
				if(a[i - 1] <= 0) ans = 0;
			} else if(acc[0][i - 1] && a[i] != -1) {
				if(a[i - 1] != -1 && a[i - 1] != a[i] + 1) ans = 0;
				a[i - 1] = a[i] + 1;
				if(a[i - 1] > k) ans = 0;
			}
		for(i = 0; i < n; i++) mrk[i] = 0;
		for(i = 0; i < n - 1; ) {
			if(a[i] != -1 || (!acc[0][i] && !acc[1][i])) { i++; continue; }
			mrk[i] = 1;
			int cur = 0, mx = 0, mn = 0;
			for(; i < n - 1 && (acc[0][i] || acc[1][i]); i++) {
				mrk[i] = 1;
				cur += acc[1][i] - acc[0][i];
				mx = max(mx, cur);
				mn = min(mn, cur);
			}
			if(mx - mn >= k) ans = 0;
			mrk[i] = 1;
			ans = mod(ans * ll(k - (mx - mn)));
			i++;
		}
		for(i = 0; i < n; i++)
			if(a[i] == -1 && !mrk[i])
				ans = mod(ans * k);
		printf("%lld\n", ans);
	}
}

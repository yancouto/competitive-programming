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

int a[712][712];

int main() {
	int i, j, n;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++)
				scanf("%d", &a[i][j]);
			sort(a[i], a[i] + n);
		}
		int mx = INT_MAX;
		ll sum = 0;
		for(i = n - 1; i >= 0; i--) {
			for(j = n - 1; j >= 0 && a[i][j] >= mx; j--);
			if(j < 0) break;
			mx = a[i][j];
			sum += a[i][j];
		}
		if(i >= 0) puts("-1");
		else printf("%lld\n", sum);
	}
}

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

int a[1123];

int main() {
	for_tests(t, tt) {
		int i, n;
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		sort(a, a + n);
		int left = n;
		int tot = 0;
		for(i = n - 1; i >= 0; i--) {
			int mn = (50 + a[i] - 1) / a[i];
			if(mn > left) break;
			tot++; left -= mn;
		}
		printf("Case #%d: %d\n", tt, tot);
	}
}

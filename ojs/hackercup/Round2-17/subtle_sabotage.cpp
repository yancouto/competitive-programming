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

inline int go(int n, int m, int k) {
	int mn = INT_MAX;
	if(n - 2 > 2 * k && k < m) mn = min(mn, (m + k - 1) / k);
	if(k == 1 && n > 2 && m > 4) mn = min(mn, 5);
	if(k == 1 && n == 2 && m > 4) mn = min(mn, 2);
	if(k > 1 && n > 2 * k && m > 2 * k + 2) mn = min(mn, 4);
	return mn;
}

int main() {
	for_tests(t, tt) {
		int n, m, k;
		scanf("%d %d %d", &n, &m, &k);
		int mn = INT_MAX;
		mn = min(mn, go(n, m, k));
		mn = min(mn, go(m, n, k));
		printf("Case #%d: ", tt);
		if(mn == INT_MAX) puts("-1");
		else printf("%d\n", mn);
	}
}

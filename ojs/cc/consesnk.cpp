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

int L, n;
int s[1123456];

ll solve(ll x) {
	ll tot = 0;
	for(ll i = 0; i < n; i++)
		tot += abs(x + i * ll(L) - ll(s[i]));
	return tot;
}

int main() {
	int i, a, b;
	for_tests(t, tt) {
		scanf("%d %d %d %d", &n, &L, &a, &b);
		for(i = 0; i < n; i++) scanf("%d", &s[i]);
		sort(s, s + n);
		int l = 0, r = b - a - n * L;
		while(l < r) {
			int m = (l + r) / 2;
			if(solve(m + a) >= solve(m + 1 + a)) l = m + 1;
			else r = m;
		}
		printf("%lld\n", solve(l + a));
	}
}

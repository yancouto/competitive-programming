#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

ll a[100009];
int main() {
	int i, n; ll p;
	for_tests(t, tt) {
		scanf("%d %lld", &n, &p);
		for(i = 0; i < n; i++)
			scanf("%lld", &a[i]);
		int r = -1;
		ll tot = 0;
		ll all = 0;
		for(i = 0; i < n; i++) {
			if(i) tot -= a[i - 1];
			while(r + 1 < n && tot + a[r + 1] <= p) tot += a[++r];
			all += (r - i + 1);
		}
		printf("Case #%d: %lld\n", tt, all);
	}
}

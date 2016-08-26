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

const int N = 112345;
ll r[N], d[N];

int main() {
	int i, n, q; ll x, y;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n; i++) {
		scanf("%lld", &r[i]);
		r[i] *= r[i];
	}
	for(i = 0; i < q; i++) {
		scanf("%lld %lld", &x, &y);
		d[i] = x * x + y * y;
	}
	sort(d, d + q);
	int j = 0;
	ll tot = 0;
	for(i = 0; i < q; i++) {
		while(j < n && d[i] > r[j])
			j++;
		tot += n - j;
	}
	printf("%lld\n", tot);
}

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
const int N = 4000009;
bool dv[N];
int ps[N], pn;

int main() {
	int i, j, n;
	for(i = 2; i < N; i++)
		if(!dv[i]) {
			ps[pn++] = i;
			for(j = i + i; j < N; j += i)
				dv[i] = true;
		}
	while(scanf("%d", &n) != EOF && n) {
		ll tot = 0;
		for(i = 0; i < pn && ps[i] < n; i++) {
			ll k = ps[i];
			for(; k <= n; k *= ps[i]) {
				ll x = (n / k - n / (k * ps[i]));
				ll o = n / k;
				printf("%lld mult of %lld all %lld\n", x, k, o);
				tot += (x * ll(o - x) + (x * (x - 1)) / 2ll) * ll(k);
			}
		}
		printf("%lld\n", tot);
	}
}

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
const ll modn = 1000000009;
inline ll mod(ll x) { return x % modn; }

ll pd[2][303][303];
int main() {
	int n, k, i, cur, mx;
	scanf("%d %d", &n, &k);
	pd[n&1][0][k] = 1;
	for(i = n - 1; i >= 0; i--)
		for(cur = 0; cur <= n; cur++)
			for(mx = cur; mx <= n; mx++) {
				ll &r = pd[i&1][cur][mx]; int j = !(i&1);
				r = pd[j][cur][mx] + pd[j][cur + 1][mx + (mx == cur)];
				if(cur) r += pd[j][cur - 1][mx];
				r = mod(r);
			}
	printf("%d\n", (int) pd[0][0][0]);
}

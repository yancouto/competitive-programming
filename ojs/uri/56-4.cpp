#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
const int MAX = 50009;
ll x[MAX], y[MAX];
ll dist(ll xx, int i) {
	return (xx - x[i]*10000ll) * (xx - x[i]*10000ll) + y[i] * y[i] * 100000000ll;
}

int main() {
	int n, i, X;
	scanf("%d %d", &n, &X);
	for(i = 0; i < n; i++)
		scanf("%lld %lld", &x[i], &y[i]);
	int l = 0, r = X * 10000; ll a;
	while(l < r) {
		int mid = (l + r + 1) / 2;
		int mx = 0; ll d = dist(mid, 0);
		for(i = 1; i < n; i++)
			if((a = dist(mid, i)) > d) {
				mx = i;
				d = a;
			}
		if(x[mx]*10000 >= mid) l = mid;
		else r = mid - 1;
	}
	int mx = 0; ll d = dist(l, 0);
	for(i = 1; i < n; i++)
		if((a = dist(l, i)) > d) {
			mx = i;
			d = a;
		}
	printf("%.2f %.2f\n", l / 10000., sqrt(d) / 10000.);
}

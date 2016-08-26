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

const int N = 1000009;
struct li {
	ll a, b; // y = ax + b
	double end;
};
double x_inter(li l1, li l2) {
	return double(l2.b - l1.b) / (l1.a - l2.a);
}
li st[N]; int sn;

ll max_x(ll x) {
	int l = 0, r = sn - 1;
	while(l < r) {
		int m = (l + r) / 2;
		if(st[m].end >= x) r = m;
		else l = m + 1;
	}
	return st[l].a * x + st[l].b;
}

ll dp[N];
int a[N], d[N];
int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d", &a[i], &d[i]);
	for(i = n - 1; i >= 0; i--) {
		li l = {-(i + 1), dp[i + 1], 1/0.};
		while(sn > 1 && x_inter(st[sn - 1], l) <= st[sn - 2].end) sn--;
		if(sn) st[sn - 1].end = x_inter(st[sn - 1], l);
		st[sn++] = l;
		dp[i] = max_x(d[i]) + a[i] + ll(d[i]) * i;
	}
	printf("%lld\n", *max_element(dp, dp + n + 1));
}

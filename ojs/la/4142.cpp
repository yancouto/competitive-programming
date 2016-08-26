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
const int N = 1009;
ll v1[N], v2[N];
ll *wacc = v1 + 1, *xwacc = v2 + 1;
int x[N];
ll dp[N][N];

struct li {
	ll a, b; //y = ax + b
	double end;
};

double x_inter(li l1, li l2) {
	return double(l2.b - l1.b) / (l1.a - l2.a);
}
li st[N]; int sn;

ll min_x(ll x) {
	int l = 0, r = sn - 1;
	while(l < r) {
		int m = (l + r) / 2;
		if(st[sn - 1 - m].end >= x) r = m;
		else l = m + 1;
	}
	l = sn - 1 - l;
	return st[l].a * x + st[l].b;
}

int n;
void calc(int k) {
	sn = 0;
	for(int i = n - 1; i >= 0; i--) {
		li l = {-x[i], dp[i + 1][k - 1] + ll(x[i]) * wacc[i] - xwacc[i]};
		while(sn && x_inter(st[sn - 1], l) >= st[sn - 1].end) sn--;
		l.end = sn? x_inter(st[sn - 1], l) : 1/0.;
		st[sn++] = l;
		dp[i][k] = min_x(wacc[i - 1]) + xwacc[i - 1];
	}
}

int main() {
	int i, k, w;
	while(scanf("%d %d", &n, &k) != EOF) {
		for(i = 0; i < n; i++) {
			scanf("%d %d", &x[i], &w);
			wacc[i] = wacc[i - 1] + w;
			xwacc[i] = xwacc[i - 1] + ll(w) * ll(x[i]);
		}
		for(i = 0; i < n; i++)
			dp[i][0] = 10000000000000000ll;
		for(i = 0; i <= k; i++)
			dp[n][i] = 0;
		for(i = 1; i <= k; i++)
			calc(i);
		printf("%lld\n", dp[0][k]);
	}
}

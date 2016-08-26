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

double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
int a[2009];
int n, L, W;
int seen[2009][2009];
double memo[2009][2009];
double solve(int l, int r) {
	if(l + r == n) return 0;
	double &ans  = memo[l][r];
	if(seen[l][r]) return ans;
	seen[l][r] = 1;
	ans = 1/0.;
	if(l < n/2) ans = solve(l + 1, r) + dist(a[l+r], 0, l * (L / (n / 2. - 1.)), 0);
	if(r < n/2) ans = min(ans, solve(l, r + 1) + dist(a[l+r], 0, r * (L / (n / 2. - 1.)), W));
	return ans;
}

int main() {
	int i;
	while(scanf("%d", &n) != EOF) {
		scanf("%d %d", &L, &W);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		sort(a, a + n);
		memset(seen, 0, sizeof seen);
		printf("%.12f\n", solve(0, 0));
	}
}

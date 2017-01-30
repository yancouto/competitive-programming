#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
const double pi = acos(-1);
double a[1123];

int main() {
	int i, j; double r;
	scanf("%d %lf", &n, &r);
	for(i = 0; i < n; i++) scanf("%lf", &a[i]);
	sort(a, a + n);
	double tot = pi * r * r * n;
	for(i = 1; i < n; i++) {
		double d = a[i] - a[i - 1];
		if(d > 2 * r) continue;
		double alp = acos((d / 2.) / r);
		double h = sqrt(r * r - d * d / 4.);
		tot -= 2 * alp * r * r - d * h;
	}
	printf("%.20f\n", tot);
}

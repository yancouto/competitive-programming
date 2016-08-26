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
const int N = 212345;

int n;
int a[N];
double solve(double x) {
	double tot = 0;
	for(int i = 0; i < n; i++)
		tot += sqrt(1. + double(double(a[i]) - (x + i)) * double(double(a[i]) - (x + i)));
	return tot;
}

int main() {
	int i;
	scanf("%d", &n); n *= 2;
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a + n);
	double l = -1e8, r = 1e8;
	while(clock() < 0.92 * CLOCKS_PER_SEC) {
		double q1 = (2.*l + r) / 3.;
		double q2 = (l + 2.*r) / 3.;
		double a1 = solve(q1), a2 = solve(q2);
		if(a1 > a2) l = q1;
		else r = q2;
	}
	printf("%.22f\n", solve((l + r) / 2.));
}

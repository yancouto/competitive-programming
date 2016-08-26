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
#define double long double

int s[N], x[N], p[N], n;

double memo[N];
int seen[N];
double solve(int i) {
	if(i == n) return 0;
	double &r = memo[i];
	if(seen[i]) return r;
	seen[i] = true;
	r = 1/0.;
	double d = 0;
	for(int j = i; j < i + 100 && j < n; j++) {
		d += s[j];
		r = min(r, solve(j + 1) + x[j] + d);
		d = d * (1. + (p[j] / 100.));
	}
	return r;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d %d %d", &s[i], &x[i], &p[i]);
#undef double
	printf("%.15f\n", (double) solve(0));
}

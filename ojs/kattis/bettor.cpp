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

double x, p;
double memo[10000][20009];
bool seen[10000][20009];
double s(int d) { return (d >= 0? 1. : (1. - x)) * d; }
double solve(int i, int v) {
	if(i == 10000) return s(v);
	double &r = memo[i][v + 1002];
	if(seen[i][v + 10002]) return r;
	seen[i][v + 10002] = true;
	return r = max(s(v), p * solve(i + 1, v + 1) + (1. - p) * solve(i + 1, v - 1));
}

int main() {
	scanf("%lf %lf", &x, &p); x /= 100.; p /= 100.;
	printf("%.10f\n", solve(0, 0));
}

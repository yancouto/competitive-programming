#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

int es, ef;
double memo[10000][2];
int seen[10000][2];
double solve(int e, bool beg) {
	if(e <= 0) return 
	double &r = memo[e][beg];
	if(seen[e][beg]) return r;
	seen[e][beg] = true;
	double l = 0, r = 1;
	for(i = 0; i < 30; i++) {
		double m1 = (2.*l + r) / 3.;
		double m2 = (l + 2.*r) / 3.;
		double ans = solve(e - es, false);


	}

}

int main() {
	int i, j, n, e;
	scanf("%d %d %d", &e, &es, &ef);
	printf("%.6f\n", solve(e, true));
}

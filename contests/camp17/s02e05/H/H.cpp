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

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;

int s, m, p;
bool geq(double x) {
	double S = s;
	int M = m;
	while(M--) {
		double a = (S * p / 100.);
		if(a <= x)
			S -= (x - a);
		else
			S += (a - x);
		if(S <= 0) return true;
	}
	return false;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j;
	scanf("%d %d %d", &s, &m, &p);
	double l = 0, r = 1e9;
	for(i = 0; i < 10000; i++) {
		double mid = (l + r) / 2;
		if(geq(mid)) r = mid;
		else l = mid;
	}
	printf("%.10f\n", l);
}

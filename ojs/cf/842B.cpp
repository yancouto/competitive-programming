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
typedef long double dbl;
const dbl eps = 1e-9;

dbl dist(int x, int y) {
	return sqrtl(x * x + y * y);
}


int main() {
	int i, j, n, R, d, x, y, r;
	rd(R); rd(d); rd(n);
	int ct = 0;
	for(i = 0; i < n; i++) {
		rd(x); rd(y); rd(r);
		if(dist(x, y) - r >= R - d - eps && dist(x, y) + r <= R + eps)
			ct++;
	}
	printf("%d\n", ct);
}

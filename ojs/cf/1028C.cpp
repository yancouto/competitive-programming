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
#	define debug(args...) ((void) 0)
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
const int N = 212345;
int xb[N], yb[N], xu[N], yu[N];
int xbr[N], ybr[N], xur[N], yur[N];

int mx(int a, int b) { return max(a, b); }
int mn(int a, int b) { return min(a, b); }

void add(int a[], int acc[], int (*fn)(int, int)) {
	acc[n - 1] = a[n - 1];
	for(int i = n - 2; i >= 0; i--)
		acc[i] = fn(a[i], acc[i + 1]);
}

int main() {
	int i, j;
	rd(n);
	for(i = 0; i < n; i++) rd(xb[i]), rd(yb[i]), rd(xu[i]), rd(yu[i]);
	add(xb, xbr, mx); xbr[n] = INT_MIN;
	add(yb, ybr, mx); ybr[n] = INT_MIN;
	add(xu, xur, mn); xur[n] = INT_MAX;
	add(yu, yur, mn); yur[n] = INT_MAX;
	int xl = INT_MIN, xr = INT_MAX;
	int yl = INT_MIN, yr = INT_MAX;
	for(i = 0; i < n; i++) {
		int xl_ = max(xl, xbr[i + 1]);
		int xr_ = min(xr, xur[i + 1]);
		int yl_ = max(yl, ybr[i + 1]);
		int yr_ = min(yr, yur[i + 1]);
		if(xl_ <= xr_ && yl_ <= yr_) {
			printf("%d %d\n", xl_, yl_);
			return 0;
		}
		xl = max(xl, xb[i]);
		xr = min(xr, xu[i]);
		yl = max(yl, yb[i]);
		yr = min(yr, yu[i]);
	}
}

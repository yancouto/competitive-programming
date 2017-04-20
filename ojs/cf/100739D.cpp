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

int n, m; ll k;
const int N = 1123;
ll a[N][N], r[N], c[N];

int main() {
	int i, j;
	rd(n); rd(m); rd(k);
	int ct = 0;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			rd(a[i][j]), ct += !!a[i][j];
	if(n == 1) {
		printf("%d\n", ct);
		for(j = 0; j < m; j++)
			printf("%lld ", (k - a[0][j]) % k);
	} else if(m == 1) {
		printf("%d\n", ct);
		for(i = 0; i < n; i++)
			printf("%lld ", (k - a[i][0]) % k);
	}
	for(j = 1; j < m; j++)
		c[j] = (a[0][0] - a[0][j] + k) % k;
	for(i = 0; i < n; i++)
		r[i] = (k - a[i][0]) % k;
	ll mn = (accumulate(c, c + m, 0ll) + accumulate(r, r + n, 0ll));
	ll mnt = 0;
	for(int g = 0; g < n + m; g++) {
		ll t = (g < n? r[g] : k - c[g - n]) % k;
		ll tot = 0;
		for(i = 0; i < n; i++)
			tot += (r[i] - t + k) % k;
		for(j = 0; j < m; j++)
			tot += (c[j] + t) % k;
		if(tot < mn) mn = tot, mnt = t;
	}
	printf("%lld\n", mn);
	for(i = 0; i < n; i++)
		printf("%lld%c", (r[i] - mnt + k) % k, " \n"[i == n - 1]);
	for(j = 0; j < m; j++)
		printf("%lld%c", (c[j] + mnt) % k, " \n"[j == m - 1]);
}

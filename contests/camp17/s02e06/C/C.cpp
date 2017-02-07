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
const int N = 1123456;
int c[N], a[N], b[N], p[N];
int seen[N];

int main() {
	int i, j;
	rd(n);
	for(i = 0; i < n; i++) rd(c[i]);
	for(i = 0; i < n; i++) rd(a[i]), a[i]--;
	for(i = 0; i < n; i++) rd(b[i]), b[i]--;
	for(i = 0; i < n; i++) p[b[i]] = a[i];
	ll tot = 0;
	ll ma = *min_element(c, c + n);
	for(i = 0; i < n; i++) {
		if(seen[i]) continue;
		ll mn = LLONG_MAX, sum = 0;
		int sz = 0;
		j = i;
		do {
			seen[j] = true;
			mn = min<ll>(mn, c[j]);
			sum += c[j];
			sz++;
			j = p[j];
		} while(j != i);
		tot += min(mn * ll(sz - 1) + (sum - mn), mn + ma + sum + ma * ll(sz));
	}
	printf("%lld\n", tot);
}

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
ll a[212345];

int main() {
	int i;
	rd(n);
	for(i = 0; i < n; i++) rd(a[i]);
	ll tot = 0;
	ll sum = 0;
	map<int, ll> mp;
	for(i = n - 1; i >= 0; i--) {
		tot += sum - ll(n - i - 1) * a[i];
		tot -= mp[a[i] + 1];
		tot += mp[a[i] - 1];
		mp[a[i]]++;
		sum += a[i];
	}
	printf("%lld\n", tot);
}

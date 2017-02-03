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

const int N = 57;
const int M = 5e5+7;

int n;
ll a[N];
bool sieve[M];
ll memo[M][N];

ll pd (int s, int i) {
	if (i == n) return !sieve[s];

	ll & me = memo[s][i];
	if (me != -1)
		return me;

	if (i && a[i-1] == a[i]) return me = pd(s, i+1);
	
	me = pd(s, i+1);
	ll acc = 0;
	for (int j = i; j < n && a[i] == a[j]; j++) {
		acc += a[j];
		me += pd(s+acc, j+1);
	}
	return me;
}

int main() {
	memset(memo, -1, sizeof memo);
	sieve[0] = sieve[1] = 1;
	for (ll i = 2; i < M; i++) {
		if (sieve[i]) continue;
		for (ll j = i*i; j < M; j += i)
			sieve[j] = 1;
	}

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	sort(a, a+n);
	printf("%lld\n", pd(0, 0));
}

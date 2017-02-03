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

ll n;

int main() {
#ifdef ONLINE_JUDGE
	freopen("nim.txt", "r", stdin);
	freopen("nim.txt", "w", stdout);
#endif

	scanf("%lld", &n);

	deque<ll> mn;
	mn.push_back(0);

	ll i = 0;
	for (i = 1; i*i <= n; i++) {
		ll j = mn.back();
		mn.pop_back();
		mn.push_front(j);
/*
		j = mn.back();
		mn.pop_back();
		mn.push_front(j);
*/
		
		mn.push_front(i);
	}

	if (mn[(n+i-1)%i])
		printf("WIN\n");
	else
		printf("LOSE\n");
}

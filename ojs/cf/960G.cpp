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

ll dp(ll n, int a) {
	if(n == 0) return a == 0;
	return dp(n - 1, a - 1) + (n - 1) * dp(n - 1, a);
}

int n;

int main() {
	int i, j;
	for(i = 1; i <= 6; i++) {
		for(j = 1; j <= i; j++)
			printf("%d ", dp(i, j));
		printf("\n");
	}
}

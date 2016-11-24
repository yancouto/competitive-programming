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

int main() {
	int i, j, x, y;
	rd(n); rd(y);
	if(2 * y + 1 > n) { puts("Impossible"); return 0; }
	printf("%d\n", n);
	for(i = 0; i < y; i++) printf("%d %d ", y, y + 1);
	printf("%d", y);
	for(i = 2 * y + 1; i < n; i++)
		printf(" %d", y);
	putchar('\n');
}

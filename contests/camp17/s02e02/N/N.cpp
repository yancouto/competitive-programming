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
ll s, p;

int main() {
	scanf("%lld %lld", &s, &p);

	if (s == p) {
		printf("1\n");
		return 0;
	}
	if(p == 1) { printf("%lld\n", s); return 0; }
	if(p < s) { puts("-1"); return 0; }

	double prev = -1/0.;
	for(int i = 2; i <= 100000; i++) {
		double cur = pow(double(s) / i, i);
		if(cur <= prev && i >= 10000) break;
		if(cur >= p) {
			printf("%d\n", i);
			return 0;
		}
		prev = cur;
	}
	printf("-1\n");

}

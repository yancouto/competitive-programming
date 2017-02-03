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
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j;
	ll A, B, C;
	cin >> A >> B >> C;
	int cur = 0;
	ll p = 1, q = 1;
	for(i = 1; i <= 20000000; i++) {
		p = (((A * p + (p % B))) % C);
		q = (((A * q + (q % B))) % C);
		q = (((A * q + (q % B))) % C);
		cur++;
		//printf("[%d] %lld vs %lld\n", cur, p, q);
		if(p == q) {
			//printf("cur %d\n", cur);
			int sz = 0;
			do {
				p = (((A * p + (p % B))) % C);
				sz++;
			} while(p != q);
			ll p = 1;
			ll q = 1;
			for(i = 0; i < sz; i++) p = (((A * p + (p % B))) % C);
			int l = 0;
			while(p != q) {
				l++;
				p = (((A * p + (p % B))) % C);
				q = (((A * q + (q % B))) % C);
			}
			printf("%d\n", l + sz);
			return 0;
		}
	}
	puts("-1");
}

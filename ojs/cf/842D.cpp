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

const int N = (1 << 19);

int a[N];


inline int sum(int l, int r) {
	return a[r] - (l? a[l - 1] : 0);
}

int main() {
	int i, j, n, m, x;
	rd(n); rd(m);
	for(i = 0; i < n; i++) {
		rd(x);
		a[x] = 1;
	}
	for(i = 1; i < (1 << 19); i++)
		a[i] += a[i - 1];
	x = 0; int y;
	while(m--) {
		rd(y);
		x ^= y;
		int l = 0, r = (1 << 19) - 1;
		for(i = 18; i >= 0; i--) {
			int m = (l + r) / 2;
			int b = ((x >> i) & 1);
			if(b) {
				if(sum(m + 1, r) < r - m) l = m + 1;
				else r = m;
			} else {
				if(sum(l, m) < m - l + 1) r = m;
				else l = m + 1;
			}
		}
		printf("%d\n", x ^ l);
	}

}

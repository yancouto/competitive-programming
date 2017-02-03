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

const int N = 31;
const int M = 1e3+7;

int n;
int l, a[N];
int y;
int visi[N][M][N], turn;
int memo[N][M][N];

int pd (int i, int l, int c) {
	if (l < 0) return n+1;
	if (i == n) {
		if (l < y*c + y) return c;
		return n+1;
	}
	
	int & me = memo[i][l][c];
	if (visi[i][l][c] == turn) return me;
	visi[i][l][c] = turn;

	me = min(pd(i+1, l-a[i], c+1), pd(i+1, l, c));
	return me;
}

int main() {
	rd(l);
	rd(n);

	for (int i = 0; i < n; i++)
		rd(a[i]);
	sort(a, a+n);

	int mn = n;
	for (int i = 0; i < n; i++) {
		turn++;
		int x = 0;
		y = a[i];
		for (int j = 0; j < i; j++) {
			x += a[j];
		}

		mn = min(mn, pd(i+1, l-x, i));
	}

	printf("%d\n", mn);
}

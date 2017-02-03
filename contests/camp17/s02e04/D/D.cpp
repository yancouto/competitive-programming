

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
ll l, r;

const int M = 59049;
const int N = 66;

char visi[M][N][2], turn;
ll memo[M][N][2];
int a[N];
int v[N];

void get (ll x) {
	turn++;
	for (int i = N-1; i >= 0; i--) {
		a[i] = (x%10);
		v[i] = !x;
		x /= 10;
	}
}

ll pd (int mask, int i, int b){ 
	if (i == N) return 1;

	ll & me = memo[mask][i][b];

	if (visi[mask][i][b] == turn) return me;
	visi[mask][i][b] = turn;

	me = 0;

	if (v[i]) {
		me += pd(0, i+1, 0);
		return me;
	}
	
	int mm = 1;
	for (int j = 0; j < 10; j++) {
		if (!b && j > a[i]) break;
		int st = (mask/mm)%3;
		if (st != 2) {
			if (!mask && !j)
				me += pd(mask, i+1, (j < a[i] || b));
			else
				me += pd(mask+mm, i+1, (j < a[i] || b));
		}
		mm *= 3;
	}
	return me;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("exchange.in", "r", stdin);
	freopen("exchange.out", "w", stdout);
#endif
	scanf("%lld %lld", &l, &r);

	get(r);
	ll rs = pd(0,0,0);
	get(l-1);
	rs -= pd(0,0,0);
	printf("%lld\n", rs);
}

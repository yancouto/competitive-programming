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

const int N = 607;
const int K = 57;

int n;
int k;
ll memo[K][N];
ll a[N][N];

ll cost (int i, int j) {
	return a[j][n] - a[j][j] - a[i][n] + a[i][j];
}

ll pd (int k, int i) {
	if (k == 1) return cost(0,i);

	ll & me = memo[k][i];
	if (me != -1) return me;

	me = -a[n][n] - 3;
	for (int j = i-1; j > 0; j--)
		me = max(me, pd(k-1, j) + cost(j,i));
	return me;
}

void build (int k, int i) {
	if (k != 1) {
		ll me = pd(k,i);

		for (int j = i-1; j > 0; j--) {
			if (me == pd(k-1, j) + cost(j,i)) {
				build(k-1,j);
				break;
			}
		}
	}
	
	printf("%d ", i);
}

int main() {
	memset(memo, -1, sizeof memo);
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1];
		}
		for (int j = i+1; j <= n; j++) {
			scanf(" %lld", &a[i][j]);
			a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
		}
	}

	int best = n-1;
	for (int i = 1; i < n; i++) {
		if (pd(k,i) > pd(k,best))
			best = i;
	}

	build(k,best);
	printf("\n");
}

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

const int N = 257;
const int M = 357;
const int A = 1e3+6;

int n, t;
int q[A], v[A];
int memo[2][M][N];
int visi[2][M][N], turn;

int pd (int i, int j, int x) {
	if (i == n) return 1;
	if (x < 0) return 0;
	
	int & me = memo[i&1][j][x];
	if (visi[i&1][j][x] + 1 >= turn) return me;
	visi[i&1][j][x] = turn;

	if (j >= q[i]) {
		me = pd(i+1, j-q[i], q[i+1]-v[i+1]);
	} else {
		me = mod(pd(i, j+1, x) + pd(i, j+t+1, x-1));
	}

	return me;
}

int main() {
	 #ifdef ONLINE_JUDGE
		freopen("kebab.in", "r", stdin);
		freopen("kebab.out", "w", stdout);
	#endif
	int i, j;
	scanf("%d %d", &n, &t);
	for(i = 0; i < n; i++) scanf("%d %d", &q[i], &v[i]);

	turn = 7;

	for (int i = n-1; i >= 0; i--) {
		turn++;
		for (int j = M-1; j >= 0; j--)
			for (int x = 0; x < N; x++)
				pd(i, j, x);
	}

	printf("%d\n", pd(0, 0, q[0]-v[0]));
}

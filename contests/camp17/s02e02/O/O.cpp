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

const int N = 51;
const int M = 5e4+1;
const int K = 10;

int n, k;
int a[N];
int acc[M];
ll choose[N][N];
ll memo[N][M][K];

ll pd (int i, int s, int k) {
	if (s >= M) return 0;
	if (k < 0) return 0;

	if (i == n) 
		return (k == 0)*acc[s];
	
	ll & me = memo[i][s][k];
	if (me != -1) return me;

	me = pd(i+1, s+a[i], k-1) + pd(i+1, s, k);
	return me;
}

int main() {
	memset(memo, -1, sizeof memo);
	scanf("%d", &n);
	
	ll res = 1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		acc[a[i]]++;
	}

	for (int i = M-2; i >= 0; i--)
		acc[i] += acc[i+1];
	scanf("%d", &k);

	for (ll i = 0; i < N; i++)
		choose[0][i] = 0;
	for (ll i = 0; i < N; i++)
		choose[i][0] = 1;
	for (ll i = 1; i < N; i++)
		for (ll j = 1; j < N; j++)
			choose[i][j] = choose[i-1][j-1] + choose[i-1][j];
	
	printf("%lld\n", choose[n][k] - pd(0, 0, k-1));
}

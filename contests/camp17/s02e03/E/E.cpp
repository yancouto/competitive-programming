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

const int N = 207;

int d[N][N];
int memo[N][N];
int r[N];
int n, k;

int pd (int i, int u) {
	if (i == 0) return !u;

	int & me = memo[i][u];
	if (me != -1) return me;

	me = 0;

	for (int j = 0; j < n; j++) {
		if (d[u][j] != r[i-1]) continue;
		me |= pd(i-1, j);
	}

	return me;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	memset(memo, -1, sizeof memo);
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &d[i][j]);

	scanf("%d", &k);

	for (int i = 0; i < k; i++)
		scanf("%d", &r[i]);

	int res = 0;
	for (int i = 0; i < n; i++)
		if (pd(k,i)) res++;
	printf("%d\n", res);

	for (int i = 0; i < n; i++)
		if (pd(k,i))
			printf("%d ", i+1);
	printf("\n");
}

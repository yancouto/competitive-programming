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

const int N = 2e2+7;

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
int a, b;
char str[N];
int memo[N][N][N];

int pd (int i, int a, int b) {
	if (a < 0 || b < 0) return N+7;
	if (i == n) {
		if (!a && !b) return 0;
		return N+7;
	}

	int & me = memo[i][a][b];
	if (me != -1) return me;
	me = N+7;

	me = min(me, pd(i+1, a-1, b) + (str[i] != '0'));
	me = min(me, pd(i+1, a, b-1) + (str[i] != '1'));
	me = min(me, pd(i+1, a, b) + (str[i] != '2'));
	return me;
}

void build (int i, int a, int b) {
	if (i == n) return;

	int me = pd(i,a,b);
	if (me == pd(i+1, a-1, b) + (str[i] != '0')) {
		printf("0");
		build(i+1, a-1, b);
	} else if (me == pd(i+1, a, b-1) + (str[i] != '1')) {
		printf("1");
		build(i+1, a, b-1);
	} else if (me == pd(i+1, a, b) + (str[i] != '2')) {
		printf("2");
		build(i+1, a, b);
	}
}

int main() {
	memset(memo, -1, sizeof memo);
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	rd(n);
	rd(a);
	rd(b);
	
	scanf(" %s", str);
	int res = pd(0,a,b);
	if (res == N+7) {
		printf("-1\n");
	} else {
		printf("%d\n", pd(0, a, b));
		build(0,a,b);
	}
}

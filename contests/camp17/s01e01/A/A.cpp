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

template<class num> inline void read(num &x) {
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

const int N = 3009;
ll c[N][N];
ll x[N], y[N];
double ct[N][N], add[N], add2[N], yt[N];

int main() {
	int i, j;
	read(n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			read(c[i][j]);
	for(i = 0; i < n; i++)
		read(y[i]), x[i] = y[i];
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			x[i] += c[i][j];
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			ct[i][j] = double(c[i][j]) / x[j];
	for(i = 0; i < n; i++)
		scanf("%lf", &yt[i]);
	while(clock() < 1.8 * CLOCKS_PER_SEC) {
		memset(add2, 0, sizeof add2);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				add2[i] += ct[i][j] * (yt[j] + add[j]);
		for(i = 0; i < n; i++)
			add[i] = add2[i];
	}
	for(i = 0; i < n; i++)
		printf("%.20f\n", yt[i] + add[i]);
}

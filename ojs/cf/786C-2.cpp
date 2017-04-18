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

const int N = 112345, L = 20;

int nx[N][L], a[N];
inline int go(int i, int x) {
	int oi = i;
	for(int j = 0; (1 << j) <= x; j++)
		if((x >> j) & 1)
			i = nx[i][j];
	return i;
}

int main() {
	int i, j, k;
	rd(n);
	for(i = 0; i < n; i++) rd(a[i]);
	nx[n][0] = n;
	for(i = n - 1; i >= 0; i--)
		if(a[i] != a[i + 1])
			nx[i][0] = i + 1;
		else
			nx[i][0] = nx[i + 1][0];
	for(i = n; i >= 0; i--)
		for(j = 1; j < L; j++)
			nx[i][j] = nx[nx[i][j - 1]][j - 1];
	for(k = 1; k <= n; k++) {
		int ct = 0;
		i = 0;
		while(i < n) {
			i = go(i, k);
			ct++;
		}
		printf("%d%c", ct, " \n"[k == n]);
	}
}

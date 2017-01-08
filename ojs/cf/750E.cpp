// otario
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
const int N = 212345;
char s[N];
int nx[8][N], ct[8][N], ct2[8][N], g1[20][N];
deque<int> oc[8];

inline int c(int l, int r, int d=6) {
	return ct2[d][r] - (l? ct2[d][l - 1] : 0);
}

int main() {
	int i, a, b, d, q;
	rd(n); rd(q);
	scanf(" %s", s);
	for(d = 0; d <= 7; d++) {
		nx[d][n] = n;
		ct[d][n] = 0;
		for(i = n - 1; i >= 0; i--)
			if(s[i] == '0' + d)
				nx[d][i] = i, ct[d][n] = ct[d][n + 1] + 1, oc[d].push_front(i);
			else
				nx[d][i] = nx[d][i + 1], ct[d][n] = ct[d][n + 1];
		for(i = 0; i <= n; i++)
			ct2[d][i] = (i? ct2[d][i - 1] : 0) + (s[i] == d + '0');
	}
	g1[0][n] = n;
	for(i = n - 1; i >= 0; i--) {
		if(s[i] != '1') continue;
		if(nx[1][i + 1] == n) { g1[0][i] = n;  continue; }
		if(c(i, nx[1][i + 1], 6)) g1[0][i] = nx[1][i + 1];
		else {
			g1[0][i] = nx[1][i + 1];
			while(g1[0][i] != n && c(i, g1[0][i], 6) < c(i, g1[0][i], 1) - 1)
				g1[0][i] = g1[0][g1[0][i]];
		}
	}
	for(d = 1; d < 20; d++)
		for(i = 0; i <= n; i++)
			g1[d][i] = g1[d - 1][g1[d - 1][i]];
	while(q--) {
		rd(a); rd(b); a--; b--;
		//printf("%s\n", string(s).substr(a, b - a + 1).c_str());
		a = nx[2][a];
		a = nx[0][a];
		if(a > b) { puts("-1"); continue; }
		if(nx[7][nx[1][a]] > b) { puts("-1"); continue; }
		int l = ct2[1][a], r = ct2[1][b] - 1;
		while(l < r) {
			int m = (l + r + 1) / 2;
			if(nx[7][oc[1][m]] <= b) l = m;
			else r = m - 1;
		}
		//printf("1 at %d\n", oc[1][l]);
		//printf("[%d]%d - [%d]%d\n", b, ct2[6][b], oc[1][l], ct2[6][oc[1][l]]);
		int ba = a;
		a = nx[1][a];
		for(d = 19; d >= 0; d--)
			if(g1[d][a] <= oc[1][l])
				a = g1[d][a];
		printf("%d\n", c(a, b, 6) + (c(ba, a, 1) - 1));
	}
}

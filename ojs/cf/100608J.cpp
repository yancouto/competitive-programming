// ERROU
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

const int N = 2009;
int n, m;
char g[N][N];
inline bool v(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m && g[i][j] == '#'; }
inline bool valid(int i, int j) { return v(i, j); }

int memo1[N][N];
int memo2[N][N];
int memo3[N][N];
int memo4[N][N];
int r[N][N], u[N][N], d[N][N];

int RU(int, int);
int UR(int, int);
int RD(int, int);
int DR(int, int);
inline void mx(int &r, int x) { r = max(r, x); }

int RU(int i, int j) {
	if(!valid(i, j)) return 0;
	int &r = memo1[i][j];
	if(r != -1) return r;
	r = 0;
	if(v(i, j + 1)) mx(r, RU(i, j + 1));
	else if(v(i - 1, j)) mx(r, UR(i - 1, j) + 1);
	//if(v(i - 1, j) && v(i, j + 1) && u[i][j] > u[i][j + 1]) mx(r, 1);
	return r;
}

int UR(int i, int j) {
	if(!valid(i, j)) return 0;
	int &r = memo2[i][j];
	if(r != -1) return r;
	r = 0;
	if(i - 1 >= 0 && g[i - 1][j] == '#') r = UR(i - 1, j);
	else if(j + 1 < m && g[i][j + 1] == '#') r = RU(i, j + 1) + 1;
	//if(v(i - 1, j) && v(i, j + 1) && ::r[i][j] > ::r[i - 1][j]) mx(r, 1);
	return r;
}

int RD(int i, int j) {
	if(!valid(i, j)) return 0;
	int &r = memo3[i][j];
	if(r != -1) return r;
	r = 0;
	if(j + 1 < m && g[i][j + 1] == '#') r = RD(i, j + 1);
	else if(i + 1 < n && g[i + 1][j] == '#') r = DR(i + 1, j) + 1;
	//if(v(i, j + 1) && v(i + 1, j) && d[i][j] > d[i][j + 1]) mx(r, 1);
	return r;
}

int DR(int i, int j) {
	if(!valid(i, j)) return 0;
	int &r = memo4[i][j];
	if(r != -1) return r;
	r = 0;
	if(i + 1 < n && g[i + 1][j] == '#') r = DR(i + 1, j);
	else if(j + 1 < m && g[i][j + 1] == '#') r = RD(i, j + 1) + 1;
	//if(v(i + 1, j) && v(i, j + 1) && ::r[i][j] > ::r[i + 1][j]) mx(r, 1);
	return r;
}
int mrk[N][N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("jinxiety.in", "r", stdin);
	freopen("jinxiety.out", "w", stdout);
#endif
	int i, j;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf(" %c", &g[i][j]),
				memo1[i][j] = memo2[i][j] = memo3[i][j] = memo4[i][j] = -1, r[i][j] = u[i][j] = d[i][j] = (g[i][j] == '#'), mrk[i][j] = 0;
		for(i = 0; i < n; i++)
			for(j = m - 2; j >= 0; j--)
				if(r[i][j]) r[i][j] += r[i][j + 1];
		for(i = 1; i < n; i++)
			for(j = 0; j < m; j++)
				if(u[i][j]) u[i][j] += u[i - 1][j];
		for(i = n - 2; i >= 0; i--)
			for(j = 0; j < m; j++)
				if(d[i][j]) d[i][j] += d[i + 1][j];
		int ans = 0;
		for(i = j = 0; i < n && !d[i][j]; i++)
			for(j = 0; j < m && !d[i][j]; j++);
		mrk[i][j] = 1;
		if(v(i, j + 1)) for(; j < m; j++) mrk[i][j] = 1;
		else if(v(i + 1, j)) for(; i < n; i++) mrk[i][j] = 1;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				if(d[i][j] && !mrk[i][j])
					ans = 1;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				ans = max(ans, max(min(UR(i, j), RU(i, j)), min(DR(i, j), RD(i, j))));
		printf("%d\n", ans);
	}
}

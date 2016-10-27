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

const char lt[] = "NEWS";

const int mv[4][2] = {
	{-1, 0},
	{0, 1},
	{0, -1},
	{1, 0}
};

int ts;
const int N = 307;
int l, c;
int vs[N][N];
int sn[N][N];
char str[N][N][5];
char trash[5];
int qu[N*N][2];
int fil, fic;
int qi, qf;
int ds[N][N];

int bfs (int sl, int sc) {
	int l = sl;
	int c = sc;
	sn[l][c] = ts;
	ds[l][c] = 0;

	qi = qf = 0;
	qu[qf][0] = l;
	qu[qf][1] = c;
	qf++;

	while (qi < qf) {
		l = qu[qi][0];
		c = qu[qi][1];
		qi++;

		for (int k = 0; str[l][c][k]; k++) {
			if (str[l][c][k] == '*') continue;
			int d;
			for (d = 0; d < 4 && lt[d] != str[l][c][k]; d++);

			int nl = l + mv[d][0];
			int nc = c + mv[d][1];
			
			if (sn[nl][nc] == ts) continue;
			sn[nl][nc] = ts;
			ds[nl][nc] = ds[l][c] + 1;
			
			qu[qf][0] = nl;
			qu[qf][1] = nc;
			qf++;
		}
	}

	return ds[fil][fic];
}

void dfs (int l, int c) {
	vs[l][c] = ts;

	scanf(" %s", str[l][c]);

	for (int k = 0; str[l][c][k]; k++) {
		if (str[l][c][k] == '*') {
			fil = l;
			fic = c;
			continue;
		}
		int d;
		for (d = 0; d < 4 && lt[d] != str[l][c][k]; d++);

		int nl = l + mv[d][0];
		int nc = c + mv[d][1];
		
		if (vs[nl][nc] == ts) continue;

		printf("%c\n", lt[d]);
		fflush(stdout);

		dfs(nl, nc);

		printf("%c\n", lt[3-d]);
		fflush(stdout);
		scanf(" %s", trash);
	}
}

int main() {
	scanf("%d", &ts);
	ts++;

	while (--ts) {
		fil = fic = -1;
		l = c = N/2;

		dfs(l, c);

		if (fil == -1) 
			printf("-1\n");
		else
			printf("%d\n", bfs(N/2, N/2));
		fflush(stdout);
	}
}


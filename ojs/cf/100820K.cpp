#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

#define tm alsdhaslihd
int w;
unsigned tm = 0;
bool ok;
int di[4] = {1, -1, 1, -1};
int dj[4] = {1, 1, -1, -1};
int n;
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < n; }
char g[100][100];

bool go(int i, int j) {
	if(w == 0) { ok = true; return true; }
	if(!(tm++ % 10000) && clock() > 1.87 * CLOCKS_PER_SEC) return true;
	for(int d = 0; d < 4; d++) {
		int ni = i + di[d], nj = j + dj[d];
		int mi = ni + di[d], mj = nj + dj[d];
		if(!valid(ni, nj) || g[ni][nj] != 'W' || !valid(mi, mj) || g[mi][mj] != '_') continue;
		g[ni][nj] = '_'; w--;
		bool done = go(mi, mj);
		g[ni][nj] = 'W'; w++;
		if(done) return true;
	}
	return false;
}

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf(" %c", &g[i][j]);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			w += (g[i][j] == 'W');
	int ct = 0, si, sj;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(g[i][j] == 'B') {
				g[i][j] = '_';
				go(i, j);
				if(ok) {
					ct++;
					si = i; sj = j; ok = false;
				}
				if(ct >= 2) { puts("Multiple"); return 0; }
				g[i][j] = 'B';
			}
	if(ct == 1) printf("%c%d\n", 'a' + sj, n - si);
	else puts("None");
}

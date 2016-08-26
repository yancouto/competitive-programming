#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};
char g[12][12];
int f[256], w, h;
int seen[12][12][4], seen2[12][12];
inline bool valid(int i, int j) { return i >= 0 && i < w && j >= 0 && j < h && g[i][j] == '.'; }

int main() {
	int i, j, si, sj, d;
	scanf("%d %d", &w, &h);
	f['U'] = 0; f['D'] = 2;
	f['R'] = 1; f['L'] = 3;
	for(i = 0; i < w; i++)
		for(j = 0; j < h; j++) {
			scanf(" %c", &g[i][j]);
			if(g[i][j] != '.' && g[i][j] != '*') {
				si = i, sj = j; d = f[g[i][j]];
				g[i][j] = '.';
			}
		}
	int ct = 0;
	while(!seen[si][sj][d]) {
		seen[si][sj][d] = true;
		ct += !seen2[si][sj];
		seen2[si][sj] = true;
		int ni = si + di[d], nj = sj + dj[d];
		if(!valid(ni, nj)) d = (d + 1) % 4;
		else si = ni, sj = nj;
	}
	printf("%d\n", ct);
}

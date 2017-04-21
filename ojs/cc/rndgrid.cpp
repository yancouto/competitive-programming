#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

bitset<10009> seen[10009];
char s[10009];

const int N = 1123;
char g[N][N];
int acc[N][N];

int main() {
	int i, j, l, n;
	for_tests(tn, tt) {
		scanf("%d %d", &l, &n);
		scanf("%s", s);
		for(i = 0; i < n; i++)
			scanf("%s", g[i]);
		for(i = 0; i <= n; i++)
			acc[i][n] = acc[n][i] = 0;
		for(i = n - 1; i >= 0; i--)
			for(j = n - 1; j >= 0; j--)
				acc[i][j] = acc[i + 1][j] + acc[i][j + 1] - acc[i + 1][j + 1] + (g[i][j] == '#');
		vector<pii> ac;
		vector<int> mv;
		ac.pb(pii(0, 0)); mv.pb(-1);
		int pi = 0, pj = 0;
		seen[0 + 5001][0 + 5001] = 1;
		int mni = 0, mxi = 0, mxj = 0, mnj = 0;
		for(i = 0; s[i]; i++) {
			if(s[i] == 'R') pj++;
			else if(s[i] == 'L') pj--;
			else if(s[i] == 'U') pi--;
			else pi++;
			if(!seen[pi + 5001][pj + 5001]) {
				seen[pi + 5001][pj + 5001] = 1;
				ac.pb(pii(pi, pj)); mv.pb(i);
			}
			mxi = max(mxi, pi);
			mni = min(mni, pi);
			mxj = max(mxj, pj);
			mnj = min(mnj, pj);
		}
		for(pii p : ac) seen[p.fst + 5001][p.snd + 5001] = 0;
		int ans = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				if(g[i][j] != '.') continue;
				if(i + mni >= 0 && i + mxi < n && j + mnj >= 0 && j + mxj < n) {
					int ct = acc[i + mni][j + mnj];
					ct -= acc[i + mxi + 1][j + mnj] + acc[i + mni][j + mxj + 1];
					ct += acc[i + mxi + 1][j + mxj + 1];
					if(!ct) {
						ans ^= l;
						continue;
					}
				}
				int cur = l;
				for(int k = 0; k < (int) ac.size(); k++) {
					pi = i + ac[k].fst;
					pj = j + ac[k].snd;
					if(pi < 0 || pi >= n || pj < 0 || pj >= n || g[pi][pj] == '#') {
						cur = mv[k];
						break;
					}
				}
				ans ^= cur;
			}
		printf("%d\n", ans);
	}
}

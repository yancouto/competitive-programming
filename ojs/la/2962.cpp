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
int f[256]; char c[26];
int tme[26][26]; char cr[26][26];
char s[202]; int k;
int memo[202][202][26];
int seen[202][202], t;
void solve(int i, int j) {
	if(seen[i][j] == t) return;
	seen[i][j] = t;
	for(int g = 0; g < ::k; g++)
		memo[i][j][g] = 1000000000;
	if(i == j) { memo[i][j][f[s[i]]] = 0; return; }
	for(int k = i; k < j; k++) {
		solve(i, k); solve(k + 1, j);
		for(int x = 0; x < ::k; x++)
			for(int y = 0; y < ::k; y++) {
				int &g = memo[i][j][f[cr[x][y]]];
				g = min(g, memo[i][k][x] + memo[k+1][j][y] + tme[x][y]);
			}
	}
}

int main() {
	bool first = true;
	int i, j, n; char cc;
	while(scanf("%d", &k) != EOF && k) {
		if(!first) putchar('\n');
		first = false;
		for(i = 0; i < k; i++) {
			scanf(" %c", &c[i]);
			f[c[i]] = i;
		}
		for(i = 0; i < k; i++)
			for(j = 0; j < k; j++)
				scanf("%d- %c", &tme[i][j], &cr[i][j]);
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%s", s);
			int x = strlen(s);
			t++;
			int mn_i = 0;
			solve(0, x - 1);
			for(j = 1; j < k; j++)
				if(memo[0][x - 1][j] < memo[0][x - 1][mn_i])
					mn_i = j;
			printf("%d-%c\n", memo[0][x - 1][mn_i], c[mn_i]);
		}
	}
}

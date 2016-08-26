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
const int inf = 2e8;
char a[32], b[32]; int v[32];
vector<int> adj[26];

char s[109];
int memo[26][102][102];

int main() {
	int i, l, r, m, c, n; char m1;
	for_tests(t, tt) {
		printf("CASE #%d\n", tt);
		scanf("%d %d", &n, &m);
		for(i = 0; i < 26; i++) adj[i].clear();
		for(i = 0; i < n; i++) {
			scanf(" %c %c %c %d", &m1, &a[i], &b[i], &v[i]);
			a[i] -= 'A'; b[i] -= 'A';
			adj[m1 - 'A'].pb(i);
		}
		for(i = 0; i < m; i++) {
			scanf("%d %s", &n, s);
			for(c = 0; c < 26; c++)
				for(l = 0; l < n; l++)
					memo[c][l][l] = (s[l] - 'a' == c)? 1 : inf;
			for(l = n - 1; l >= 0; l--)
				for(r = l + 1; r < n; r++)
					for(c = 0; c < 26; c++) {
						int &R = memo[c][l][r];
						R = inf;
						for(int e : adj[c])
							for(int j = l; j < r; j++)
								R = min(R, v[e] + memo[a[e]][l][j] + memo[b[e]][j + 1][r]);
					}
			if(memo[0][0][n - 1] == inf) printf("IMPOSSIBLE\n");
			else printf("POSSIBLE WITH %d DIAMONDS\n", memo[0][0][n - 1]);
		}
	}
}

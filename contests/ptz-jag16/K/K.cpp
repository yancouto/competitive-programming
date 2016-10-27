#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 1e3+4;
const int K = 53;
const ll INF = 1e14;

int n, m;
ll memo[2][N][N];
int opt[2][N][N];
ll v[N];

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		scanf("%lld", v+i);

	sort(v, v+n);

	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			memo[0][i][j] = INF;

	for (int i = 0; i < n; i++) {
		memo[0][i][i] = 0;
		opt[0][i][i] = 0;
	}
	
	for (int k = 1 ; k <= m; k++) {
		for (int i = 0; i < n; i++) {
			memo[k&1][i][i] = 0;
			opt[k&1][i][i] = i;
		}
		for (int t = 1; t < n; t++) {
			for (int i = 0; i + t < n; i++) {
				ll & me = memo[k&1][i][i+t];
				int & op = opt[k&1][i][i+t];

				me = INF;
				op = i;
				for (int x = min(opt[k&1][i][i+t-1], i+t-1); x <= opt[k&1][i+1][i+t] && x < i+t; x++) {
					ll loc = memo[!(k&1)][i][x] + memo[!(k&1)][x+1][i+t] + v[i+t] - v[x];
					if (loc <= me) {
						me = loc;
						op = x;
					}
				}
			}
		}
	}

	printf("%lld\n", memo[(m&1)][0][n-1]);
}

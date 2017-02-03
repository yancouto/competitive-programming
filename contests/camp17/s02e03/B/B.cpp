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

int n, m;
const int N = 112;
char g[N][N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j;
	scanf("%d %d", &n, &m);
	for(i = 2; i <= n+1; i++)
		for(j = 2; j <= m+1; j++)
			scanf(" %c", &g[i][j]), g[i][j] -= '0';
	int tot = 0;
	for(i = 1; i < N - 1; i++)
		for(j = 1; j < N - 1; j++) {
			if(g[i][j]) tot += 2;
			tot += abs(g[i][j] - g[i + 1][j]);
			tot += abs(g[i][j] - g[i][j + 1]);
		}
	printf("%d\n", tot);
}

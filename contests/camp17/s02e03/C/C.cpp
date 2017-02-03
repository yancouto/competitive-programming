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

int n;

int memo[1 << 25];
bool seen[1 << 25];
int l[50];
int solve(int i) {
	assert(i >= 0);
	if(i == 0) return 0;
	int &m = memo[i];
	if(seen[i]) return m;
	seen[i] = true;
	int f = __builtin_ctz(i);
	return m = (solve(i - (1 << f)) | l[f]);
}

char g[50][50];

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			scanf(" %c", &g[i][j]);
			if(g[i][j] == '*') l[i] |= (1 << j);
		}
	int mn = INT_MAX;
	for(i = 0; i < (1 << n); i++) {
		int val = solve(i);
		int fr = n - __builtin_popcount(i);
		//printf("[%d] max(%d, %d)\n", i, fr, __bult
		mn = min(mn, max(fr, __builtin_popcount(solve(i))));
	}
	printf("%d\n", mn);
}

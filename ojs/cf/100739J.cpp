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

const int M = 34;
ll acc[M][M];
char s[M];
int n;

inline int pairs(int x) { return (x * (n + n - x)) / 2; }

ll memo[M * M / 2][M * M / 2][M / 2];
ll solve(int l, int i, int j, int r, int sz) {
	if(i == j + 1) return sz? ll(1e18) : acc[l][r];
	if(i == j) return sz? ll(1e18) : acc[l][i - 1] + acc[j + 1][r];
	ll &ret = memo[pairs(l) + i][pairs(j) + r][sz];
	if(ret != -1) return ret;
	ret = min(acc[l][i - 1] + solve(i + 1, i + 1, j, r, sz), solve(l, i, j - 1, j - 1, sz) + acc[j + 1][r]);
	if(s[i] == s[j] && sz) ret = min(ret, solve(l, i + 1, j - 1, r, sz - 1));
	return ret;
}

const int N = 11234;
int a[N], b[N], c[N];

int main() {
	int i, j, k;
	memset(memo, -1, sizeof memo);
	int r; ll b;
	scanf("%d %d %lld", &n, &r, &b);
	scanf("%s", s);
	for(i = 0; i < r; i++)
		scanf("%d %d %d", &a[i], &::b[i], &c[i]), a[i]--, ::b[i]--;
	for(i = 0; i < n; i++)
		for(j = i; j < n; j++)
			for(k = 0; k < r; k++)
				if(i <= a[k] && j >= ::b[k])
					acc[i][j] += c[k];
	int mx = 0;
	for(i = 2; i <= n; i += 2)
		if(solve(0, 0, n - 1, n - 1, i / 2) <= b)
			mx = i;
	printf("%d\n", mx);
}

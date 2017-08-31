#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back
#define fst first
#define snd second

const int N = 32;

int n;

ll memo[N][N][N];

ll pd (int l, int r, int q) {
	if (l == 0 && r == 0 && q == 0)
		return 1;

	ll & me = memo[l][r][q];
	if (me != -1)
		return me;

	me = 0;

	for (int i = 0; i < l; i++)
		me += pd(i, r, q+(l-i-1));
	for (int i = 0; i < r; i++)
		me += pd(l, i, q+(r-i-1));
	if (l == 0 && q)
		me += pd(l, r, q-1);
	if (r == 0 && q)
		me += pd(l, r, q-1);
		
	return me;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("permutominoes.in", "r", stdin);
	freopen("permutominoes.out", "w", stdout);
#endif
	memset(memo, -1, sizeof memo);

	int n;
	scanf("%d", &n);

	ll res = 0;

	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			res += pd(i, n - j - 1, j - i - 1);

	printf("%lld\n", res);
}

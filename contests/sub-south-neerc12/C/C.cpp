#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 1e6+7;

int memo[N][10];

int pd (int n, int f) {
	if (n < 0)
		return N;
	if (n == 0)
		return 0;

	int & me = memo[n][f];
	if (me != -1)
		return me;
	
	me = N;
	for (int k = 1; k <= 6; k++)
		me = min(me, pd(n-21+k*(f!=0)+f,7-k) + 1);
	return me;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	memset(memo, -1, sizeof memo);
	
	int n;
	scanf("%d", &n);
	int rs = pd(n,0);
	if (rs == N)
		rs = -1;
	printf("%d\n", rs);
}

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
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

char want[1123];
char conc[112345];
int n, k;
int h[30];

int memo[302][100001];
ll solve(int i, int j) {
	if(i == k) return 1;
	if(j >= n) return 0;
	int &r = memo[i][j];
	if(r != -1) return r;
	r = solve(i, j + 1);
	if(want[i] == conc[j])
		r = mod(r + solve(i + 1, j + 1 + h[want[i] - 'A']));
	return r;
}

int main() {
	int i;
	scanf("%d %d", &k, &n);
	for(i = 0; i < 26; i++) scanf("%d", &h[i]);
	scanf(" %s %s", want, conc);
	memset(memo, -1, sizeof memo);
	printf("%lld\n", solve(0, 0));
}

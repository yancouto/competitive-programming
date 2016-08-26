#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int memo[302][302*302];
bool seen[302][302*302];
int a[302], n, o[302];
int solve(int i, int sum) {
	if(i == n) return sum? 100000 : 0;
	int &r = memo[i][sum];
	if(seen[i][sum]) return r;
	seen[i][sum] = 1;
	r = min(solve(i + 1, sum + a[i]) + (o[i] != 1), solve(i + 1, sum - a[i]) + (o[i] != -1));
	return r;
}

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d ", &a[i]);
		if(i < n - 1) o[i + 1] = (getchar() == '+'? 1 : -1);
	}
	int x = solve(1, a[0]);
	if(x > 500) puts("-1");
	else printf("%d\n", x);
}

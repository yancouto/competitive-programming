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

int seen[103][10090], cur;
int memo[103][10090], a[200], n, all;
int solve(int i, int sum) {
	if(i == n) return abs(all - 2 * sum);
	if(seen[i][sum] == cur) return memo[i][sum];
	seen[i][sum] = cur;
	return memo[i][sum] = min(solve(i + 1, sum), solve(i + 1, sum + a[i]));
}

void build(int i, int sum) {
	if(i == n) return;
	if(solve(i, sum) == solve(i + 1, sum)) build(i + 1, sum);
	else printf("%d ", i + 1), build(i + 1, sum + a[i]);
}

double b[200];
int main() {
	int i;
	while(scanf("%d", &n) && n) {
		double tot = 0;
		for(i = 0; i < n; i++) {
			scanf("%lf", &b[i]);
			tot += b[i];
		}
		all = 0; cur++;
		for(i = 0; i < n; i++)
			a[i] = int(b[i] * 10000. / tot), all += a[i];
		solve(0, 0);
		build(0, 0); putchar('\n');
	}
}

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

int n;
int memo[2009][2009];
int w[2123], c[2123];
int solve(int i, int s) {
	if(i == n) return 0;
	int &r = memo[i][s];
	if(r != -1) return r;
	r = solve(i + 1, s);
	if(w[i] <= s) r = max(r, c[i] + solve(i + 1, s - w[i]));
	return r;
}

int main() {
	int s, i;
	scanf("%d %d", &s, &n);
	for(i = 0; i < n; i++)
		scanf("%d %d", &w[i], &c[i]);
	memset(memo, -1, sizeof memo);
	printf("%d\n", solve(0, s));
}

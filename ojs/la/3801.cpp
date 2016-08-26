// wrong
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
const int MAX = 1003;
int a[MAX][MAX], n;
int memo[MAX][MAX][2];
int solve(int i, int j, bool left) {
	if(i >= n) return 0;
	int &r = memo[i][j][left];
	if(r != -1) return r;
	r = 0;
	if(left) r = max(r, a[i][j] + solve(i + 1, j, true));
	else r = max(r, a[i][j] + solve(i + 1, j, true) + solve(i + 1, j + 1, false));
	return r;
}

int main() {
	int i, j;
	while(scanf("%d", &n) != EOF && n) {
		for(i = 0; i < n; i++)
			for(j = 0; j <= i; j++)
				scanf("%d", &a[i][j]);
		memset(memo, -1, sizeof memo);
		printf("%d\n", solve(0, 0, false));
	}
}

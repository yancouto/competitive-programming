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


vector<int> sum[10009];
unordered_map<int, bool> mp[102][102];
bool solve(int x, int y, int bm) {
	if(x < y) return solve(y, x, bm);
	if((bm & (bm - 1)) == 0) return 1;
	if(mp[x][y].count(bm)) return mp[x][y][bm];
	for(int i = 1; i < x; i++)
		for(int b : sum[i * y])
			if((b | bm) == bm && solve(i, y, b) && solve(x - i, y, bm ^ b))
				return mp[x][y][bm] = 1;
	for(int i = 1; i < y; i++)
		for(int b : sum[i * x])
			if((b | bm) == bm && solve(x, i, b) && solve(x, y - i, bm ^ b))
				return mp[x][y][bm] = 1;
	return mp[x][y][bm] = 0;
}

int a[20];
int main() {
	int i, j, n, x, y, tt = 0;
	while(scanf("%d", &n) != EOF && n) {
		scanf("%d %d", &x, &y);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		printf("Case %d: ", ++tt);
		if(accumulate(a, a + n, 0ll) != x * y) { puts("No"); continue; }
		for(i = 0; i <= x * y; i++) sum[i].clear();
		for(i = 0; i <= x; i++)
			for(j = i; j <= y; j++)
				mp[i][j].clear(), mp[j][i].clear();
		for(i = 0; i < (1 << n); i++) {
			int s = 0;
			for(j = 0; j < n; j++)
				if(i & (1 << j))
					s += a[j];
			sum[s].pb(i);
		}
		if(solve(x, y, (1 << n) - 1)) puts("Yes");
		else puts("No");
	}

}

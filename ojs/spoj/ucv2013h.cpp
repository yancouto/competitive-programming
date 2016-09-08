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
const int N = 500;

int n, m;
int seen[N][N], a[N][N];
int dfs(int i, int j) {
	if(!a[i][j] || seen[i][j] || !i || !j || i > n || j > m) return 0;
	seen[i][j] = 1;
	int v = 1;
	return 1 + dfs(i + 1, j) + dfs(i - 1, j) + dfs(i, j + 1) + dfs(i, j - 1);
}

int main() {
	int i, j;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++)
				scanf("%d", &a[i][j]), seen[i][j] = 0;
		map<int, int> mp;
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++)
				if(!seen[i][j] && a[i][j])
					mp[dfs(i, j)]++;
		int sum = 0;
		for(auto e : mp) sum += e.snd;
		printf("%d\n", sum);
		for(auto e : mp)
			printf("%d %d\n", e.fst, e.snd);
	}
}

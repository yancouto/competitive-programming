#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000009;
inline ll mod(ll x) { return x % modn; }

const int N = 1003;
int memo[N][N][11], a[N], b[N];
int n, m;
ll solve(int i, int j, int k) {
	if(k == 0) return 1;
	if(i == n || j == m) return 0;
	int &r = memo[i][j][k];
	if(r != -1) return r;
	r = 0;
	r = mod(solve(i + 1, j, k) + solve(i, j + 1, k) - solve(i + 1, j + 1, k) + modn);
	if(a[i] > b[j]) r = mod(r + solve(i + 1, j + 1, k - 1));
	return r;
}

int main() {
	freopen("team.in", "r", stdin);
	freopen("team.out", "w", stdout);
	int i, k;
	scanf("%d %d %d", &n, &m, &k);
	memset(memo, -1, sizeof memo);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	for(i = 0; i < m; i++) scanf("%d", &b[i]);
	printf("%d\n", (int) solve(0, 0, k));
}

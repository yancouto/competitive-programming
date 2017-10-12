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

int n, m;

char x[42][412];

int memo[42][42][412][11];
int solve(int l, int r, int d, int v) {
	if(l > r) return 0;
	if(d == m) return 0;
	if(v == 10) return 100000000;
	int &re = memo[l][r][d][v];
	if(re != -1) return re;
	re = solve(l, r, d, v + 1);
	int ct = 0;
	for(int i = l; i <= r; i++) {
		ct += (x[i][d] != '0' + v);
		re = min(re, ct + solve(l, i, d + 1, 0) + solve(i + 1, r, d, v + 1));
	}
	return re;
}

void build(int l, int r, int d, int v) {
	if(l > r || d == m) return;
	int re = solve(l, r, d, v);
	if(re == solve(l, r, d, v + 1)) return build(l, r, d, v + 1);
	int ct = 0;
	for(int i = l; i <= r; i++) {
		ct += (x[i][d] != '0' + v);
		x[i][d] = '0' + v;
		if(re == ct + solve(l, i, d + 1, 0) + solve(i + 1, r, d, v + 1)) {
			build(l, i, d + 1, 0);
			return build(i + 1, r, d, v + 1);
		}
	}
}

int main() {
	memset(memo, -1, sizeof memo);
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%s", x[i]);
	build(0, n - 1, 0, 0);
	for(int i = 0; i < n; i++) puts(x[i]);
}

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
const int N = 1123;

int memo[N][N][2];
int seen[N][N][2], t;
int o[256], id[256];
char a[N], b[N];
int n;
int solve(int l, int r, bool ri) {
	if(l > r) return 0;
	int &ans = memo[l][r][ri];
	if(seen[l][r][ri] == t) return ans;
	seen[l][r][ri] = t;
	int i = l + ((n - 1) - r);
	int c = ri? r : l;
	int *v = ri? o : id;
	int *v2 = ri? id : o;
	ans = 100000;
	if(b[i] == v[a[c]]) ans = min(ans, solve(l + !ri, r - ri, ri));
	if(b[i] == v2[a[l+r-c]]) ans = min(ans, solve(l + ri, r - !ri, !ri) + 1);
	return ans;
}

int main() {
	int i;
	for(i = 0; i < 256; i++) id[i] = o[i] = i;
	o['b'] = 'd';
	o['d'] = 'b';
	o['p'] = 'q';
	o['q'] = 'p';
	while(scanf("%d", &n) != EOF) {
		scanf("%s %s", a, b);
		t++;
		int a = solve(0, n - 1, false);
		if(a > 10000) puts("-1");
		else printf("%d\n", a);
	}
}

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
int a[N], acc[N];

int n;
int memo[1123][8223];
int solve(int i, int l) {
	int r = (i? acc[i - 1] : 0) - l;
	if(i == n) return !(l & (l - 1)) && !(r & (r - 1)) && (l == r || l == 0 || r == 0);
	int &ret = memo[i][l];
	if(ret != -1) return ret;
	if(l && !(l & (l - 1)) && (r >> __builtin_ctz(l)) <= 1) { r += l; l = 0; }
	if(r && !(r & (r - 1)) && (l >> __builtin_ctz(r)) <= 1) { l += r; r = 0; }
	ret = 0;
	if(!((a[i] - 1) & l) && solve(i + 1, l + a[i])) ret = 1;
	if(!((a[i] - 1) & r) && solve(i + 1, l)) ret = 1;
	return ret;
}

void build(int i, int l) {
	assert(solve(i, l));
	if(i == n) return;
	int r = (i? acc[i - 1] : 0) - l;
	if(l && !(l & (l - 1)) && (r >> __builtin_ctz(l)) <= 1) { r += l; l = 0; }
	if(r && !(r & (r - 1)) && (l >> __builtin_ctz(r)) <= 1) { l += r; r = 0; }
	if(!((a[i] - 1) & l) && solve(i + 1, l + a[i])) {
		putchar('l');
		build(i + 1, l + a[i]);
	}
	else {
		putchar('r');
		build(i + 1, l);
	}

}



int main() {
	int i, j;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		acc[0] = a[0];
		for(i = 1; i < n; i++) acc[i] = a[i] + acc[i - 1];
		for(i = 0; i < n; i++)
			for(j = 0; j <= acc[n - 1]; j++)
				memo[i][j] = -1;
		if(solve(0, 0)){ build(0, 0); putchar('\n'); }
		else puts("no");
	}
}

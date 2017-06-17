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

char C[112];
inline int id(int l, int r) {
	return l + r - 1;
}

const int N = 1000009;

int n;
char s[3][N];
int memo[2][3][27];
int acc[3][N];
inline ll solve(int l, int r, int i, int c, bool calc=false) {
	if(l > r) return 1;
	if(i == n) return (l == r);
	if(c >= 27) return 0;
	if(l == r) {
		if(s[l][i] != '?') return (s[l][i] >= C[c]) * acc[l][i];
		else return mod(ll('z' - C[max(c, 1)] + 1ll) * ll(acc[l][i + 1]));
	}
	int id = ::id(l, r);
	ll ret = memo[i & 1][id][c];
	if(!calc) return ret;
	ret = solve(l, r, i, c + 1);
	for(int g = l; g <= r; g++) {
		if(s[g][i] != '?' && s[g][i] != C[c]) break;
		if(c == 0 && s[g][i] == '?') break;
		ret += solve(l, g, i + 1, 0) * solve(g + 1, r, i, c + 1);
	}
	return memo[i & 1][id][c] = mod(ret);
}

int main() {
	int i, j;
	for(i = 1; i <= 26; i++) C[i] = 'a' + i - 1;
	for_tests(tn, tt) {
		n = 0;
		for(i = 0; i < 3; i++) scanf("%s", s[i]), n = max<int>(n, strlen(s[i]));
		acc[0][n] = acc[1][n] = acc[2][n] = 1;
		for(i = 0; i < 3; i++)
			for(j = n - 1; j >= 0; j--)
				if(s[i][j] == '?')
					acc[i][j] = mod(ll(acc[i][j + 1]) * 26ll);
				else
					acc[i][j] = acc[i][j + 1];
		for(i = n - 1; i >= 0; i--) {
			for(j = 26; j >= 0; j--) {
				solve(1, 2, i, j, true);
				solve(0, 1, i, j, true);
				solve(0, 2, i, j, true);
			}
		}
		printf("%lld\n", solve(0, 2, 0, 0, true));
	}
}

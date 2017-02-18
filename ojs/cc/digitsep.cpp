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

inline ll gcd(ll a, ll b) {
	while(b) {
		ll c = a % b;
		a = b;
		b = c;
	}
	return a;
}

int n, m, x, y;
char s[312];

bool memo[312][312];
ll se[312][312][312];
int sz[312][312];
void solve(int i, int us) {
	if(memo[i][us]) return;
	memo[i][us] = true;
	ll *S = se[i][us];
	if(us > y) return;
	if(i + m * (y - us) < n) return;
	if(us < x && i + (x - us) > n + 1) return;
	if(i == n) { if(us >= x) S[sz[i][us]++] = 0; return; }
	ll cur = 0;
	for(int j = 0; j < m && i + j < n; j++) {
		cur = 10ll * cur + (s[i + j] - '0');
		solve(i + j + 1, us + 1);
		for(int g = 0; g < sz[i + j + 1][us + 1]; g++)
			S[sz[i][us]++] = gcd(cur, se[i + j + 1][us + 1][g]);
	}
	sort(S, S + sz[i][us]);
	sz[i][us] = unique(S, S + sz[i][us]) - S;
}

int main() {
	for_tests(t, tt) {
		scanf("%d %s %d %d %d", &n, s, &m, &x, &y); x++; y++;
		solve(0, 0);
		printf("%lld\n", se[0][0][sz[0][0]-1]);
		for(int i = 0; i < 312; i++)
			for(int j = 0; j < 312; j++)
				memo[i][j] = 0, sz[i][j] = 0;
	}
}

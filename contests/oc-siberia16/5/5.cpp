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

int d[300], M;
ll memo[60][230][2];
ll solve(int s, int m, bool add) {
	int sg = add? 1 : -1;
	if(s <= 0) return 0;
	ll &r = memo[s][m][add];
	if(r != -1) return r;
	r = 0;
	for(int i = 0; i < M; i++) {
		if(d[i] == s) { r += (m == ((sg * i + M) % M)); }
		else r += solve(s - d[i] - 1, (m - sg * i + M) % M, true) + solve(s - d[i] - 1, (m - sg * i + M) % M, false);
	}
	for(int i = 3; i <= s; i++)
		for(int val = 0; val < M; val++)
			r += mod(solve(i - 2, val, true) * (solve(s - i - 1, (m - val * sg + M) % M, true) + solve(s - i - 1, (m - val * sg + M) % M, false)));
	if(add) r = mod(r + solve(s - 2, m, true));
	else r = mod(r + solve(s - 2, (-m + M) % M, true));
	return r;
}

int main() {
	int i, n, p;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &n, &M, &p);
	for(i = 0; i < M; i++)
		if(i < 10) d[i] = 1;
		else d[i] = 1 + d[i / 10];
	memset(memo, -1, sizeof memo);
	printf("%d\n", (int) solve(n, p, true));
}

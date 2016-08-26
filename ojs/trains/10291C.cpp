// WA
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
const ll modn = 1000000009;
inline ll mod(ll x) { return x % modn; }

ll memo[303][303];
ll solve(int n, int k) {
	if(n <= 2) return k == 0;
	if(n == 3) return k == 1;
	ll &r = memo[n][k];
	if(r != -1) return r;
	r = (k == 0);
	for(int i = 3; i < n; i++)
		r = mod(r + ll(n - i + 1) * solve(i, k - (n - i + 2 == 3)));
	return r;
}

int main() {
	memset(memo, -1, sizeof memo);
	int n, k;
	scanf("%d %d", &n, &k);
	printf("%d\n", (int) solve(n, k));
}

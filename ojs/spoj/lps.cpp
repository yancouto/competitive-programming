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

int main() {
	scanf(" %*d %s", p);
	for(i = 0; p[i]; i++)
		s[2 * i] = p[i];
	n = 2 * i - 1;
	for(i = 1; i < n; i += 2)
		s[i] = '$';
	manacher();
	int best = 0;
	for(i = 0; i < n; i += 2)
		best = max(best, int(M[i] / 2) * 2 + 1);
	for(i = 1; i < n; i += 2)
		best = max(best, int(M[i] / 2) * 2);
	printf("%d\n", best);
}

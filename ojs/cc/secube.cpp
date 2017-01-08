// INCOMPLETE
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

bitset<1000009> mrk[102];

int main() {
	int t, i, k, x;
	for(k = 2; k <= 100; k++) {
		ll k3 = k * k * k;
		for(ll z = 0; z <= k3; z++)
			mrk[k][(z * z * z) % k3] = 1;
	}
	scanf("%d", &t);
	for(i = 0; i < t; i++) {
		scanf("%d %d", &k, &x);
		x = k * k * k - x;
		if(mrk[k][x % (k * k * k)]) puts("YES");
		else puts("NO");
	}
}

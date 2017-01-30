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

ll d, r, t;

int main () {
	scanf("%lld %lld %lld", &d, &r, &t);
	ll sm, rt;
	sm = rt = 0;
	for (ll i = 4; i < 3+d; i++)
		rt += i;
	sm = rt;

	ll cr = 3 + 3 + d;
	ll ag = 3 + d;

	while (sm < r + t) {
		sm += cr;
		rt += ag;
		cr += 2;
		ag++;
	}

	printf("%lld\n", r - rt);
}

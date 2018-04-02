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

struct pt {
	ll x, y;
	pt operator - (pt o) const { return pt{x - o.x, y - o.y}; }
	ll operator ^ (pt o) const { return x * o.y - y * o.x; }
};

inline ll sign(ll x) { return (x > 0) - (x < 0); }

pt p[112345];
ll acc[112345];

int main() {
	int i, n, q;
	bool fst = true;
	while(scanf("%d %d", &n, &q) != EOF && n) {
		if(!fst) putchar('\n');
		else fst = false;
		for(i = 0; i < n; i++)
			scanf("%lld %lld", &p[i].x, &p[i].y);
		p[n] = p[0];
		for(i = 0; i < n; i++) {
			bool big = i && (acc[i - 1] > 1e17 || acc[i - 1] < -1e17);
			int sg = i? sign(acc[i - 1]) : 0;
			acc[i] = (i? acc[i - 1] : 0ll) + (p[i] ^ p[i + 1]);
			if(big) assert(sg == sign(acc[i]));
		}
		//printf("tot %lld\n", abs(acc[n - 1]));
		while(q--) {
			int a, b;
			scanf("%d %d", &a, &b);
			ll ar = acc[b - 1] - (a? acc[a - 1] : 0);
			ar += (p[b] ^ p[a]);
			//printf("ar %lld\n", abs(ar));
			ar = min(abs(ar), abs(acc[n - 1]) - abs(ar));
			assert(ar > 0);
			printf("%lld", ar / 2);
			if(ar % 2) printf(".5\n");
			else printf(".0\n");
		}
	}
}

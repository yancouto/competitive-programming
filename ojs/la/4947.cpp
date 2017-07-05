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

const int N = 112345;
ll x[N];
bool w[N];

int main() {
	int i, n; char c;
	for_tests(tn, tt) {
		scanf("%d", &n);
		ll W = 0, B = 0;
		for(i = 0; i < n; i++) {
			scanf("%lld %c", &x[i], &c);
			w[i] = (c == 'W');
			if(w[i]) W += x[i];
			else B += x[i];
		}
		if(W == 0 || B == 0) { printf("%lld\n", W + B); continue; }
		ll cW = 0, cB = 0;
		int tot = 0;
		for(i = 0; i < n; i++) {
			ll nW = cW + (w[i] * x[i]);
			ll nB = cB + ((!w[i]) * x[i]);
			if(!cW && !cB) { cW += w[i] * x[i]; cB += (!w[i]) * x[i]; continue; }
			bool les = (W * cB < B * cW); // W / B < cB / cW == needs more B
			if(les && (W * nB >= B * nW) && !((B * cW) % W)) { // got the B
				ll tgB = (B * cW) / W;
				nW = 0;
				nB = nB - tgB;
				tot++;
			} else if(!les && (W * nB <= B * nW) && !((W * cB) % B)) { // got the W
				ll tgW = (W * cB) / B;
				nW = nW - tgW;
				nB = 0;
				tot++;
			}
			cW = nW;
			cB = nB;
		}
		printf("%d\n", tot);
	}
}

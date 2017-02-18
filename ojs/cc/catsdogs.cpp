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
	for_tests(t, tt) {
		ll c, d, l;
		scanf("%lld %lld %lld", &c, &d, &l);
		if(l % 4) { puts("no"); continue; }
		if(l < d * 4 + max(0ll, c - d * 2) * 4 || l > (d + c) * 4) { puts("no"); continue; }
		puts("yes");
	}
}

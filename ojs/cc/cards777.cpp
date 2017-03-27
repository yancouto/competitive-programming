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
		ll r, b, p;
		scanf("%lld %lld %lld", &r, &b, &p); ll q = r + b - p;
		printf("%.20f\n", (p * r + q * b) / double(r + b));
	}
}

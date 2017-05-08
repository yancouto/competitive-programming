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
	ll w, h;
	scanf("%lld %lld", &w, &h);
	ll a = w * h;
	for(ll i = 1; i * i <= a; i++)
		if(!(a % i) && abs(i - (a / i)) < abs(w - h))
			w = i, h = a / i;
	printf("%lld\n", abs(w - h));
}

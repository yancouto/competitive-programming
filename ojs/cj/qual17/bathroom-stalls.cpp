#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

int main() {
	for_tests(t, tt) {
		ll n, k;
		scanf("%lld %lld", &n, &k);
		map<ll, ll> mp;
		mp[n] = 1;
		ll lstA, lstB;
		while(k > 0) {
			n = mp.rbegin()->fst;
			ll rm = min(k, mp.rbegin()->snd);
			mp[n] -= rm;
			lstA = n / 2;
			lstB = (n - 1) / 2;
			mp[n / 2] += rm;
			mp[(n - 1) / 2] += rm;
			if(mp[n] == 0) mp.erase(n);
			k -= rm;
		}
		printf("Case #%d: %lld %lld\n", tt, lstA, lstB);
	}
}

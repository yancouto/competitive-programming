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
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

#include <message.h>
#include "oops.h"

int main() {
	ll id = MyNodeId();
	ll no = NumberOfNodes();
	ll n = GetN();
	ll mx = LLONG_MIN, mn = LLONG_MAX;
	for(ll i = id; i < n; i += no) {
		ll v = GetNumber(i);
		mx = max(mx, v);
		mn = min(mn, v);
	}

	if(id) { PutLL(0, mn); PutLL(0, mx); Send(0); }
	else {
		for(ll i = 1; i < no; i++) {
			Receive(i);
			mn = min(mn, GetLL(i));
			mx = max(mx, GetLL(i));
		}
		printf("%lld\n", mx - mn);
	}
}

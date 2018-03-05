#include <bits/stdc++.h>
using namespace std;
#define a first
#define b second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int main() {
	int i, n;
	scanf("%d", &n);
	vector<pii> bad;
	vector<pii> good;
	ll W = 0;
	for(i = 0; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if(b > a) good.pb(pii(a, b));
		else
			bad.pb(pii(a, b));
	}
	sort(good.begin(), good.end());
	ll cur = W;
	for(pii p : good) {
		cur -= p.a;
		if(cur < 0) {
			W += -cur;
			cur = 0;
		}
		cur += p.b;
	}
	sort(bad.begin(), bad.end(), [](pii p, pii q) { return p.b > q.b; });
	assert(cur >= W);
	for(pii p : bad) {
		cur -= p.a;
		if(cur < 0) {
			W -= cur;
			cur = 0;
		}
		cur += p.b;
	}
	printf("%lld\n", W);
}

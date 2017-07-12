#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

ll n;
ll memo[70][10];
ll solve(int j, int carry) {
	//printf("solve(%d, %d)\n", j, carry);
	if(j == 60) return carry? -(1ll << 61) : 0;
	ll &r = memo[j][carry];
	if(r != -1) return r;
	r = -(1ll << 61);
	for(int i = 0; i < 8; i++) {
		int v = carry + __builtin_popcount(i);
		if((v & 1) != ((n >> j) & 1)) continue;
		r = max(r, 2ll * solve(j + 1, v / 2) + ll(i == 7));
	}
	return r;
}

void build(int j, int carry, ll a, ll b, ll c) {
	if(j == 60) {
		printf("%lld %lld %lld\n", a, b, c);
		return;
	}
	ll r = solve(j, carry);
	for(int i = 0; i < 8; i++) {
		int v = carry + __builtin_popcount(i);
		if((v & 1) != ((n >> j) & 1)) continue;
		if(r == 2ll * solve(j + 1, v / 2) + (i == 7)) {
			a |= ll(i & 1) << j;
			b |= ll((i >> 1) & 1) << j;
			c |= ll((i >> 2) & 1) << j;
			build(j + 1, v / 2, a, b, c);
			return;
		}
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld", &n);
		memset(memo, -1, sizeof memo);
		solve(0, 0);
		build(0, 0, 0, 0, 0);
	}
}

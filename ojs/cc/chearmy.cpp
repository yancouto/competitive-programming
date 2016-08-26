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

ll memo[20][20][2];
ll solve(int i, int o, bool odd) {
	if(i == 16) return !((o == 1 || o == 2) ^ odd);
	ll &r = memo[i][o][odd];
	if(r != -1) return r;
	r = 5ll * solve(i + 1, 0, odd ^ (o == 1 || o == 2));
	r += 5ll * solve(i + 1, (o + 1) % 4, odd);
	return r;
}

void build(int i, int o, int odd, ll x, ll v) {
	if(i == 16) {
		printf("%lld\n", v);
		return;
	}
	for(ll d = 0; d <= 9; d++) {
		if(d & 1) {
			if(solve(i + 1, (o + 1) % 4, odd) >= x) return build(i + 1, (o + 1) % 4, odd, x, v * 10ll + d);
			else x -= solve(i + 1, (o + 1) % 4, odd);
		} else {
			if(solve(i + 1, 0, odd ^ (o == 1 || o == 2)) >= x) return build(i + 1, 0, odd ^ (o == 1 || o == 2), x, v * 10ll + d);
			else x -= solve(i + 1, 0, odd ^ (o == 1 || o == 2));
		}
	}
	assert(false);
}


int main() {
	ll x;
	memset(memo, -1, sizeof memo);
	for_tests(t, tt) {
		scanf("%lld", &x);
		build(0, 0, 0, x, 0);
	}
}

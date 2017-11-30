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

ll ct[257];

ll memo2[257][257];
ll mid(int l, int r) {
	ll &m = memo2[l][r];
	if(m != -1) return m;
	m = 0;
	for(int i = l + 1; i < r; i++) {
		ll mn = min(r - i, i - l);
		m += mn * mn * ct[i];
	}
	return m;
}

ll memo[257][257];
ll solve(int i, int k) {
	ll &r = memo[i][k];
	if(r != -1) return r;
	r = 0;
	if(i == 255) return r = 0;
	if(k == 0) {
		for(int j = i + 1; j < 256; j++)
			r += (j - i) * (j - i) * ct[j];
		return r;
	}
	r = LLONG_MAX;
	for(int j = i + 1; j < 256; j++)
		r = min(r, mid(i, j) + solve(j, k - 1));
	return r;
}

int main() {
	memset(memo, -1, sizeof memo);
	memset(memo2, -1, sizeof memo2);
	int d, k;
	scanf("%d %d", &d, &k);
	while(d--) {
		int x;
		scanf("%d", &x);
		scanf("%lld", &ct[x]);
	}
	ll mn = LLONG_MAX;
	for(int i = 0; i < 256; i++) {
		ll cur = 0;
		for(int j = 0; j <= i; j++)
			cur += (i - j) * (i - j) * ct[j];
		cur += solve(i, k - 1);
		mn = min(mn, cur);
	}
	printf("%lld\n", mn);
}

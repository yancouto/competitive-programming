#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char s[11234];
ll memo[11234][50];
ll solve(int i, int add) {
	if(i == -1) return add == 0;
	ll &r = memo[i][add + 25];
	if(r != -1) return r;
	r = 0;
	int cc = s[i] + add;
	for(int c = (cc % 31); c <= 126; c += 31) {
		if(c < 32) continue;
		r += solve(i - 1, (cc - c) / 31);
	}
	return r = mod(r);
}

int main() {
	memset(memo, -1, sizeof memo);
	fgets(s, 11234, stdin);
	s[strlen(s) - 1] = 0;
	printf("%lld\n", solve(strlen(s) - 1, 0));
}

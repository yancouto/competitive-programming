#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pll;

ll N;
vector<int> p;
pll go(int i, int mx, ll x, ll div) {
	int ct = 0;
	pll ans(div, -x);
	while(mx-- && log(x) + log(p[i]) <= log(3e18)) {
		ct++;
		x *= p[i];
		if(x > N) break;
		ans = max(ans, go(i + 1, ct, x, div * ll(ct + 1)));
	}
	return ans;
}

int dv[1002];
int main() {
	int i, j, t;
	scanf("%d", &t);
	for(i = 2; i < 1000; i++)
		if(!dv[i]) {
			p.pb(i);
			for(j = i + i; j < 1000; j += i)
				dv[j] = 1;
		}
	while(t--) {
		scanf("%lld", &N);
		pll p = go(0, 100, 1, 1);
		printf("%lld %lld\n", -p.second, p.first);
	}
}

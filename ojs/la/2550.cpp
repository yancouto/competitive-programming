// TLE
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int w[20], c[20], n, m;

map<pii, ll> mp;
ll &mm(int i, int left) {
	pii p = pii(i, left);
	if(!mp.count(p)) mp[p] = -1;
	return mp[p];
}
ll solve(int i, int left) {
	if(i == n + 1) return 0;
	ll &ret = mm(i, left);
	if(ret != -1) return ret;
	for(int j = 0; j <= i; j++)
		if(left >= j * w[i])
			ret = max(ret, j * c[i] + solve(i + 1, left - j * w[i]));
	return ret;
}

int main() {
	int i;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 1; i <= n; i++)
			scanf("%d", &w[i]);
		for(i = 1; i <= n; i++)
			scanf("%d", &c[i]);
		mp.clear();
		printf("%lld\n", solve(1, m));
	}
	return 0;
}

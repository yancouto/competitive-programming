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

const int N = 112345;
char sa[N][12];
char s[12];
int a[N], nx[N];

int main() {
	int i, n, k;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++)
		scanf("%s", sa[i]);
	map<string, int> mp;
	for(i = 0; i < k; i++) {
		scanf("%s", s);
		mp[s] = i + 1;
	}
	for(i = 0; i < n; i++)
		a[i] = mp[sa[i]];
	set<int> nxs;
	for(i = 1; i <= k; i++) nx[i] = n + i, nxs.insert(n + i);
	ll ans = 0;
	for(i = n - 1; i >= 0; i--) {
		if(a[i]) {
			nxs.erase(nx[a[i]]);
			nx[a[i]] = i;
			nxs.insert(i);
		}
		int r = *nxs.rbegin();
		if(r < n)
			ans += (n - r);
	}
	printf("%lld\n", ans);
}

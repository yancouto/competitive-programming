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

int mdc(int a, int b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

int main() {
	int a, b, c, n, i;
	for_tests(t, tt) {
		map<pii, set<pii>> mp;
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			int g = mdc(a, b);
			int f = mdc(g, c);
			mp[pii(a/g, b/g)].insert(pii(c / f, g / f));
		}
		int mx = 0;
		for(auto &s : mp)
			mx = max(mx, (int)s.snd.size());
		printf("%d\n", mx);
	}
}

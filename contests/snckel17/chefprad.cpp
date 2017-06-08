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


const int N = 11234;
ll a[N], b[N], c[N];
int main() {
	int i, n, m, j; ll e;
	for_tests(tn, tt) {
		scanf("%d %d %lld", &n, &m, &e);
		for(i = 0; i < n; i++) scanf("%lld", &c[i]), c[i] -= 2 * modn;
		for(i = 0; i < m; i++) scanf("%lld", &b[i]);
		sort(c, c + n);
		sort(b, b + m);
		vector<ll> evs;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				evs.pb(b[j] - c[i] - e);
		sort(evs.begin(), evs.end());
		int ans = 0;
		for(ll t : evs) {
			for(i = 0; i < n; i++) a[i] = c[i] + t;
			j = 0;
			int ct = 0;
			for(i = 0; i < n; i++) {
				while(j < m && b[j] < a[i] - e) j++;
				if(j < m && abs(a[i] - b[j]) <= e) ct++, j++;
			}
			ans = max(ans, ct);
		}
		printf("%d\n", ans);
	}
}

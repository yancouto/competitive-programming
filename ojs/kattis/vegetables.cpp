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

int w[1123];

int main() {
	int i, n, j; double t;
	scanf("%lf %d", &t, &n);
	vector<int> pos;
	for(i = 0; i < n; i++) {
		scanf("%d", &w[i]);
		for(j = 1; j <= 501; j++)
			pos.pb((w[i] + j - 1) / j);
	}
	sort(pos.begin(), pos.end());
	pos.erase(unique(pos.begin(), pos.end()), pos.end());
	int ans = INT_MAX;
	for(int mx : pos) {
		int mn = ceil(t * mx);
		int tot = 0;
		for(i = 0; i < n; i++) {
			int cut = (w[i] + mx - 1) / mx;
			tot += cut - 1;
			if(tot > 500) break;
			if((w[i] / cut) < mn) break;
		}
		if(i == n) ans = min(ans, tot);
	}
	printf("%d\n", ans);
}

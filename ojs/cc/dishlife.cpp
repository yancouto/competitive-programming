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

vector<int> a[112345];
int ct[112345];

int main() {
	int i, j, k, n, x, p;
	for_tests(t, tt) {
		scanf("%d %d", &n, &k);
		for(i = 0; i < n; i++) a[i].clear();
		for(i = 1; i <= k; i++) ct[i] = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &p);
			while(p--) {
				scanf("%d", &x);
				a[i].pb(x);
				ct[x]++;
			}
		}
		for(i = 1; i <= k && ct[i]; i++);
		if(i <= k) puts("sad");
		else {
			for(i = 0; i < n; i++) {
				for(j = 0; j < a[i].size() && ct[a[i][j]] > 1; j++);
				if(j == a[i].size()) {
					puts("some");
					break;
				}
			}
			if(i == n) puts("all");
		}
	}
}

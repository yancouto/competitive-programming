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

const int N = 1e6+7;
ll d; int n[3];
ll a[3][N];

int main () {
	while (scanf("%lld %d %d %d", &d, &n[0], &n[1], &n[2]) != EOF) {
		for (int k = 0; k < 3; k++) for (int i = 0; i < n[k]; i++)
			scanf("%lld", &a[k][i]);

		ll res = 0;
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < n[k]; i++) {
				ll cur = 1;
				for (int j = 1; j < 3; j++) {
					int x = (j+k)%3;
					auto l = lower_bound(a[x], a[x] + n[x], a[k][i], [k,x] (int a, int b) { return pii(a,x) < pii(b,k); });
					auto r = upper_bound(a[x], a[x] + n[x], a[k][i] + d);
					//cout << k << " " << i << "[" << l - a[x] << " " << r - a[x] << "]" << endl;
					cur *= (r-l);
				}
				//cout << cur << endl;
				res += cur;
			}
		}

		printf("%lld\n", res);
	}
}

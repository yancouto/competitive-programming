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

ll a[112345];

int main() {
	int i, n, t, j; ll d;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while(t--) {
		cin >> n >> d;
		for(i = 0; i < n; i++) cin >> a[i];
		ll k = accumulate(a, a + n, 0ll);
		if(k % n) { cout << "-1\n"; continue; }
		k /= n;
		ll tot = 0;
		for(i = 0; i < d; i++) {
			for(j = i; j + d < n; j += d) {
				tot += abs(a[j] - k);
				a[j + d] += (a[j] - k);
				a[j] = k;
			}
		}
		for(i = 0; i < n && a[i] == k; i++);
		if(i == n) cout << tot << '\n';
		else cout << "-1\n";
	}
}

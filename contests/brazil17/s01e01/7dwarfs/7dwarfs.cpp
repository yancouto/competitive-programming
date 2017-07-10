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

ll n;
ll pd[2][7];

int main () {
	cin >> n;
	
	for (int i = 0; i <= n; i++) {
		ll v;
		if (i)
			cin >> v;
		for (int k = 0; k < 7; k++) {
			if (!i) {
				pd[0][k] = -1;
				pd[0][0] = 0;
			} else {
				pd[i&1][k] = pd[!(i&1)][k];
				int nk = ((k - v)%7 + 7)%7;
				if (pd[!(i&1)][nk] != -1)
					pd[i&1][k] = max(pd[i&1][k], pd[!(i&1)][nk]+v);
			}
		}
	}
	cout << pd[n&1][0] << endl;
}

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

const int N = 1e5;

ll r[N];

ll getroot (ll i) {
	return floor(sqrt(i));
}

ll f (ll n) {
	if (n < N)
		return r[n];
	return f(getroot(n)) + f(n-getroot(n)) + n;
}

int main () {
	ll n;

	r[1] = 0;
	ll s;
	for (ll i = 2; i < N; i++) {
		s = getroot(i);
		r[i] = r[s] + r[i-s] + i;
	}
	
	cin >> n;
	cout << f(n) << endl;
}

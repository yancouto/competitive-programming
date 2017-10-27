#include <bits/stdc++.h>
using namespace std;
#define double long double

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, k;

int main () {
	scanf("%lld %lld", &n, &k);
	double res = 0;

	if (k == 1) {
		res = ll(n)*(n-1)/2 + n;
	} else {
		double kt = 1;
		for (int t = 0; t <= min(n/2, 1000ll); t++) {
			if (t != 0) res += (n - 2*t + 1)/kt;
			res += (n - 2*t)/kt;
			kt *= k;
		}
	}

	cout << setprecision(20) << res << endl;
}

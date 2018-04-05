#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

typedef long double dbl;

int a[5123];

int main() {
	int i, n;
	scanf("%d", &n);
	dbl sum = 0;
	for(i = 0; i < n; i++) { scanf("%d", &a[i]); sum += a[i]; }
	if(n == 1) { printf("%d\n", a[0]); return 0; }
	sort(a,a+n);
	dbl res = dbl(a[n-1])/n;
	for (int d = 0; d < n-1; d++) {
		dbl h = 0;
		dbl ts = 0;
		for(i = d; i < n; i++) {
			h += 1. / abs(pow<dbl>(a[i], 1. / (n - d - 1.)));
			ts += a[i];
		}
		dbl ans = 0;
		for(i = d; i < n; i++) {
			dbl loc = abs(pow<dbl>(a[i], -1. / (n - d - 1.))) * abs(pow<dbl>((n - d - 1.) / h, n - d));
			ans += loc;
		}
		//cout << (ts-ans)/(n) << " " << h << endl;
		res = max(res, (ts - ans)/(n - d));
	}
	cout << fixed << setprecision(20) <<  res << endl;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll a, b;

int main () {
	scanf("%lld %lld", &a, &b);
	ll d = a+b-2;

	ll r = d*(d+1)/2;
	if (d%2 == 0) r += b;
	else r += a;

	printf("%lld\n", r);
}

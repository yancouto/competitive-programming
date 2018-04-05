#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1e5+7;

int n, k; ll t;
ll x[N], y[N];
int vs[N];

ll go (int p) {
	ll e = (1ll<<p);
	for (int i = 0; i < n; i++) if (vs[i] != p) {
		ll c = 0, j, s = 0, u = i;
		do {
			s++;
			u = (u + e)%n;
		} while (u != i);
		ll nk = k%(s+s);
		
		for (j = 0, s = i; j < nk; j++, s = (s+e)%n)
			c ^= x[s];
		for (j = i; vs[j] != p; vs[j] = p, j = (j+e)%n, s = (s+e)%n) {
			y[j] = c; c ^= x[j] ^ x[s];
		}
	}
	for (int i = 0; i < n; i++) x[i] = y[i];
}

int main () {
	scanf("%d %d %lld", &n, &k, &t);

	for (int i = 0; i < n; i++) { scanf("%lld", &x[i]); vs[i] = -1; }
	for (int p = 0; t; p++) {
		if ((1ll<<p)&t) { 
			go(p);
			t -= (1ll<<p);
		}
	}

	for (int i = 0; i < n; i++) printf("%lld ", x[i]);
	printf("\n");
}

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const int N = 23;

set<ll> s[N];
ll a[N];
int curr;
int n;

ll getsum (int j) {
	ll res = 0;
	for (int i = 0; i < n; i++)
		if (j&(1<<i))
			res += a[i];
	return res;
}

int main () {
	scanf("%d", &n);
	ll c = 0;
	for (int i = 0; i < n; i++) {
		bool ok = 1;
		do {
			ok = 1;
			c++;
			//printf("testing %lld\n", c);
			for (int j = 0; ok && j < (1<<i); j++) {
				int cc = __builtin_popcount(j) + 1;
				ll ss = getsum(j) + c;
				//printf("test %d -> %lld\n", cc, ss);
				if (s[cc].find(ss) != s[cc].end())
					ok = 0;
			}
		} while (!ok);

		for (int j = 0; ok && j < (1<<i); j++) {
			int cc = __builtin_popcount(j) + 1;
			ll ss = getsum(j) + c;
			s[cc].insert(ss);
			//printf("add %d -> %lld\n", cc, ss);
		}
		a[i] = c;
		printf("%lld\n", a[i]);
		s[1].insert(c);
		//printf("add %d -> %lld\n", 1, c);
	}
}

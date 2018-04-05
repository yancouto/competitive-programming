#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int T = 5e4;
const int K = 20;
const int M = 1e6+2;

int n;
int a, b;
vector<int> prm;

ll c2 (ll x) { return x * (x-1) / 2; }

bool isprime (int x) {
	for (int i = 2; i*i <= x; i++) if (x%i == 0) return 0;
	return 1;
}

int main () {
	scanf("%d", &n);

	for (int i = 2; i < M; i++) if (isprime(i)) prm.pb(i);

	while (n--) {
		scanf("%d %d", &a, &b);
		ll sum = 0;

		for (int i = 0; prm[i] < T; i++)
			sum += c2(b/prm[i] - (a-1)/prm[i]);

		for (int x = 1; x <= K; x++) {
			for (int y = x; y <= K; y++) {
				int mn = max({ T, (a+x-1)/x, b/(y+1)+1});
				int mx = min({ M, b/y, (x>1)?((a+x-2)/(x-1)-1):M});
				if (mn > mx) continue;
				int q = upper_bound(prm.begin(),prm.end(),mx) - lower_bound(prm.begin(),prm.end(),mn);
				sum += c2(y-x+1)*q;
			}
		}
		printf("%lld\n", sum);
		fflush(stdout);
	}
}


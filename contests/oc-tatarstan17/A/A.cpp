#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const ll pr[] = {2,3,5,7,11,13};
const int Q = 6;

ll rr[Q];
ll k, r;
vector<ll> res;

void brute (int i, ll n, ll k) {
	if (k == 0) {
		if (n != 1)
			res.push_back(n);
		return;
	}
	if (i == Q) return;

	while (n <= r && k >= 0) {
		brute(i+1, n, k);
		if (log(n) + log(rr[i]) > log(9e18)) break;
		n *= rr[i];
		k--;
	}
}

int main () {
	for (int i = 0; i < Q; i++) {
		rr[i] = 1;
		for (int j = 0; j < pr[i]; j++)
			rr[i] *= pr[i];
	}
	
	scanf("%lld %lld", &k, &r);
	brute(0, 1, k);

	sort(res.begin(), res.end());
	printf("%d\n", int(res.size()));
	if (res.empty()) return 0;
	for (int i = 0; i < res.size(); i++) {
		if (i) putchar(' ');
		printf("%lld", res[i]);
	}
	printf("\n");
}

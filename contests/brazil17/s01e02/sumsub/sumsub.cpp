#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int main() {
	int i, n, x;
	scanf("%d", &n);
	ll acc = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		acc += x;
	}
	acc = mod(acc);
	ll acc2 = acc;
	for(i = 0; i < n - 1; i++)
		acc = mod(acc * 2ll);
	printf("%lld\n", mod(acc - acc2 + modn));
}

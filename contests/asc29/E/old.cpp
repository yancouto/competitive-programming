#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back
#define fst first
#define snd second

const int N = 1123;

ll fat[N];

inline ll choose(ll n, ll p) {
	return fat[n] / (fat[p] * fat[n - p]);
}

inline ll func(int a, int b, int c, int d) {
	printf("%d, %d, %d, %d = %lld\n", a, b, c, d, choose(a + b + c + d, a + b));
	return choose(a + b + c + d, a + b);
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("permutominoes.in", "r", stdin);
	freopen("permutominoes.out", "w", stdout);
#endif
	fat[0] = 1;
	int i;
	for(i = 1; i < N; i++)
		fat[i] = ll(i) * fat[i - 1];
	int n;
	scanf("%d", &n);
	ll tot = 0;
	for(int a = 0; a <= n; a++)
		for(int b = 0; a + b <= n; b++)
			for(int c = 0; a + b + c <= n; c++)
				tot += func(a, b, c, n - a - b-  c) * func(b, n - a - b - c, a, c);
	printf("%lld\n", tot);
}

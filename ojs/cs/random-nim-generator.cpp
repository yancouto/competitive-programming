#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 30011;
inline ll mod(ll x) { return x % modn; }

// To calculate c[i] = sum (a[j] * b[k]) st j | k == i
// Use c = itf(tf(a) * tf(b)), where * is element by element multiplication

// Common transformations and inverses:
// OR  - (a, b) => (a, a + b)     | (a, b) => (a, b - a)
// AND - (a, b) => (a + b, b)     | (a, b) => (a - b, b)
// XOR - (a, b) => (a + b, a - b) | (a, b) => ((a + b) / 2, (a - b) / 2)

typedef ll num;

// Transform a inplace (OR), initially l = 0, r = 2^n - 1
void tf(num a[], int l, int r) {
	if(l == r) return;
	int m = (l + r) / 2;
	tf(a, l, m);
	tf(a, m + 1, r);
	for(int i = l; i <= m; i++) {
		int j = (m + 1) + (i - l);
		ll A = a[i], B = a[j];
		a[i] = mod(A + B);
		a[j] = mod(A - B + modn);
	}
}

// Inverse transforms a inplace (OR), initially l = 0, r = 2^n - 1
void itf(num a[], int l, int r) {
	if(l == r) return;
	int m = (l + r) / 2;
	for(int i = l; i <= m; i++) {
		int j = (m + 1) + (i - l);
		ll A = a[i], B = a[j];
		a[i] = mod((A + B) * 15006);
		a[j] = mod((A - B + modn) * 15006);
	}
	itf(a, l, m);
	itf(a, m + 1, r);
}

ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			r = mod(r * x);
	return r;
}

ll a[1 << 17];

int main() {
	int n, k, i;
	scanf("%d %d", &n, &k);
	for(i = 0; i <= k; i++)
		a[i] = 1;
	tf(a, 0, (1 << 17) - 1);
	for(i = 0; i < (1 << 17); i++)
		a[i] = fexp(a[i], n);
	itf(a, 0, (1 << 17) - 1);
	printf("%lld\n", mod(fexp(k + 1, n) - a[0] + modn));
}

#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
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
	for(int i = l; i <= m; i++)
		a[i] += a[m + 1 + (i - l)];
}

// Inverse transforms a inplace (OR), initially l = 0, r = 2^n - 1
void itf(num a[], int l, int r) {
	if(l == r) return;
	int m = (l + r) / 2;
	for(int i = l; i <= m; i++)
		a[i] -= a[m + 1 + (i - l)];
	itf(a, l, m);
	itf(a, m + 1, r);
}

const int N = 1 << 20;
ll a[N];

int main() {
	int n, x, i, j;
	scanf("%d", &n);
	a[0] = 1;
	while(n--) {
		scanf("%d", &x);
		a[x] = 1;
	}
	tf(a, 0, (1 << 20) - 1);
	for(i = 0; i < (1 << 20); i++)
		for(j = 0; j < 20; j++)
			a[i] = mod(a[i] * a[i]);
	itf(a, 0, (1 << 20) - 1);
	int ct = 0;
	for(i = 0; i < (1 << 20); i++)
		ct += (a[i] != 0);
	printf("%d\n", ct);
}

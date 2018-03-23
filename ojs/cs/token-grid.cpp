#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char h[20][1123];

// To calculate c[i] = sum (a[j] * b[k]) st j | k == i
// Use c = itf(tf(a) * tf(b)), where * is element by element multiplication

// Common transformations and inverses:
// OR  - (a, b) => (a, a + b)     | (a, b) => (a, b - a)
// AND - (a, b) => (a + b, b)     | (a, b) => (a - b, b)
// XOR - (a, b) => (a + b, a - b) | (a, b) => ((a + b) / 2, (a - b) / 2)

typedef int num;

// Transform a inplace (OR), initially l = 0, r = 2^n - 1
void tf(num a[], int l, int r) {
	if(l == r) return;
	int m = (l + r) / 2;
	tf(a, l, m);
	tf(a, m + 1, r);
	for(int i = l; i <= m; i++)
		a[m + 1 + (i - l)] = mod(a[m + 1 + (i - l)] + a[i]);
}

// Inverse transforms a inplace (OR), initially l = 0, r = 2^n - 1
void itf(num a[], int l, int r) {
	if(l == r) return;
	int m = (l + r) / 2;
	for(int i = l; i <= m; i++)
		a[m + 1 + (i - l)] = mod(a[m + 1 + (i - l)] - a[i] + modn);
	itf(a, l, m);
	itf(a, m + 1, r);
}

int A[1 << 16], B[1 << 16];
char g[20][1123];
int ans[1123];

int ct[30];

int main() {
	int i, n, m, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		scanf("%s", g[i]);
	for(i = 0; i < (1 << 16); i++) A[i] = 1;
	for(j = 0; j < m; j++) {
		int cur = 1;
		memset(ct, 0, sizeof ct);
		for(i = 0; i < (1 << 16); i++) {
			B[i] = cur;
			int k;
			for(k = 0; ((i >> k) & 1); k++)
				if(isalpha(g[k][j]))
					cur -= (1 << (--ct[g[k][j] - 'a']));
			if(isalpha(g[k][j]))
				cur += (1 << (ct[g[k][j] - 'a']++));
		}
		for(i = 0; i < (1 << 16); i++)
			A[i] = mod(ll(A[i]) * ll(B[i]));
	}
	itf(A, 0, (1 << 16) - 1);
	for(i = 0; i < (1 << 16); i++)
		ans[__builtin_popcount(i)] = mod(A[i] + ans[__builtin_popcount(i)]);
	for(i = 0; i <= n; i++)
		printf("%d ", ans[n - i]);
	putchar('\n');
}

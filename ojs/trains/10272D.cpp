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

void tf(int a[], int l, int r) {
	if(l == r) return;
	int m = (l + r) / 2;
	tf(a, l, m);
	tf(a, m + 1, r);
	for(int i = l; i <= m; i++)
		a[m + 1 + (i - l)] += a[i];
}

void itf(int a[], int l, int r) {
	if(l == r) return;
	int m = (l + r) / 2;
	for(int i = l; i <= m; i++)
		a[m + 1 + (i - l)] -= a[i];
	itf(a, l, m);
	itf(a, m + 1, r);
}

int a[6][1 << 21];
int c[1 << 21];

int main() {
	int i, j, n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for(i = 0; i < m; i++) {
		for(j = 0; j < (1 << n); j++) {
			char c;
			scanf(" %c", &c);
			a[i][j] = c - '0';
		}
		tf(a[i], 0, (1 << n) - 1);
	}
	for(i = 0; i < k; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		for(j = 0; j < (1 << n); j++)
			c[j] = ::a[a][j] * ::a[b][j];
		itf(c, 0, (1 << n) - 1);
		for(j = 0; j < (1 << n); j++)
			putchar('0' + (c[j] > 0));
		putchar('\n');
	}
}

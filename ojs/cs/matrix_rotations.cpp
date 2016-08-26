#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 222;
int a[N][N], b[N][N];

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			b[i][j] |= a[i][j];
			b[j][n - 1 - i] |= a[i][j];
			b[n - 1 - i][n - 1 - j] |= a[i][j];
			b[n - 1 - j][n - 1 - (n - 1 - i)] |= a[i][j];
		}
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++)
			printf("%d ", b[i][j]);
		putchar('\n');
	}
}

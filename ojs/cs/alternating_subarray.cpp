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

const int N = 112345;
int a[N], alt[2][N];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	alt[0][n - 1] = alt[1][n - 1] = 1;
	for(i = n - 2; i >= 0; i--)
		alt[0][i] = 1 + (a[i] < a[i + 1]) * alt[1][i + 1],
		alt[1][i] = 1 + (a[i] > a[i + 1]) * alt[0][i + 1];
	printf("%d\n", max(*max_element(alt[0], alt[0] + n), *max_element(alt[1], alt[1] + n)));
}

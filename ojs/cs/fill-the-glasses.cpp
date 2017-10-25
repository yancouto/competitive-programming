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

int a[112345];

int main() {
	int i, n, k;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	sort(a, a + n);
	printf("%d\n", (accumulate(a, a + k, 0) + 99) / 100);
}

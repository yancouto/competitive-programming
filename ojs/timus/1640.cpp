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

int main() {
	int x, y, i, n; double d = 0;
	scanf("%d", &n);
	for(i = 0; i < n; i++) { scanf("%d %d", &x, &y); d = max(d, sqrt(x * x + y * y)); }
	printf("0 0 %.10f\n", d);
}

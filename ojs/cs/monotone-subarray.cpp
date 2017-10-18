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

#define dec asdasd
#define eq aasassa

int a[212345];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	int b = 0;
	int eq = 0, inc = 0, dec = 0;
	for(i = 0; i < n; i++) {
		if(i && a[i] != a[i - 1]) eq = 0;
		eq++;
		if(i && a[i] > a[i - 1]) dec = eq;
		else dec++;
		if(i && a[i] < a[i - 1]) inc = eq;
		else inc++;
		b = max({b, inc, dec});
	}
	printf("%d\n", b);
}

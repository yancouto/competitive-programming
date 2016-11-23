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

int a[112345];
int main() {
	int i, n, x, y, s;
	scanf("%d %d", &n, &s);
	for(i = 0; i <= n; i++) a[i] = INT_MAX;
	for(i = 0; i < n; i++) {
		scanf("%d %d", &x, &y);
		a[x] = min(a[x], y);
	}
	sort(a, a + n + 1);
	int tot = 0;
	for(i = 0; i <= n; i++)
		if(s >= a[i]) {
			s -= a[i];
			tot++;
		}
	printf("%d\n", tot);
}

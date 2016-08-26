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

int a[112345], b[112345];

int main() {
	int i, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for(i = 1; i <= n; i++)
			scanf("%d", &b[i]);
		int tot = 0;
		for(i = 1; i <= n; i++)
			tot += (b[i] <= (a[i] - a[i - 1]));
		printf("%d\n", tot);
	}
}

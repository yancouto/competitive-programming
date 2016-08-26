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

int main() {
	int i, j, n, x; char d;
	scanf("%d", &n);
	int p = INT_MIN, m = INT_MAX;
	for(i = 0; i < n; i++) {
		scanf("%d %c", &x, &d);
		if(d == '+') p = max(p, x);
		else m = min(m, x);
	}
	if(p == INT_MIN || m == INT_MAX) puts("1");
	else if(p <= m) puts("1");
	else puts("2");
}

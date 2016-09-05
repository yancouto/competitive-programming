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
	int n, k;
	scanf("%d %d", &n, &k); n--;
	int cur = 1, tot = 0;
	while(n > 0 && cur < k) {
		n -= cur;
		cur *= 2;
		tot++;
	}
	if(n < 0) n = 0;
	tot += (n + k - 1) / k;
	printf("%d\n", tot);
}

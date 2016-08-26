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
	int n, tot = 0, odd = 0, one = 0, x, i, ex = 0;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		if(x >= 2) ex += (x - 2) / 2;
		tot += x / 2;
		if(x == 1) one++;
		else odd += (x & 1);
	}
	if(one >= odd) {
		tot += one;
		one -= odd;
		tot -= min(ex, one / 2);
	} else {
		odd -= one;
		tot += one + ((odd + 1) / 2);
	}
	printf("%d\n", tot);
}

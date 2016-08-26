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
	int i, x = 0, y = 0, a;
	for(i = 0; i < 5; i++) {
		scanf("%d", &a);
		x |= (a << i);
	}
	for(i = 0; i < 5; i++) {
		scanf("%d", &a);
		y |= (a << i);
	}
	if((x ^ y) != 0x1f) puts("N");
	else puts("Y");
}

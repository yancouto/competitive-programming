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

char s[112345];
int main() {
	int i, n;
	scanf("%d", &n);
	scanf("%s", s);
	int cb = 0, ca = 0;
	int tot = 0;
	for(i = 0; i < n; i++) {
		if(s[i] == 'B') cb++;
		else tot ^= cb, cb = 0, ca++;
	}
	if(!(ca & 1)) puts("-1");
	else if(tot) puts("A");
	else puts("B");
}

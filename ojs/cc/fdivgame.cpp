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

inline int calc(ll x) {
	ll cur = 1;
	while(true) {
		if(x < cur * 2ll) return 1;
		if(x < cur * 4ll) return 2;
		if(x < cur * 6ll) return 3;
		if(x < cur * 12ll) return 0;
		cur *= 12ll;
	}
}

ll r() { return rand(); }
int main() {
	int i, n; ll x;
	for_tests(t, tt) {
		scanf("%d", &n);
		int game = 0;
		for(i = 0; i < n; i++) {
			scanf("%lld", &x);
			game ^= calc(x);
		}
		if(game) puts("Henry");
		else puts("Derek");
	}
}

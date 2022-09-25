#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif


char a[112345], b[112345];
int n;

int ty(int i) {
	if (i < 0 || i >= n) return -1;
	if (a[i] == '0' && b[i] == '0') return 0;
	if (a[i] == '1' && b[i] == '1') return 1;
	return 2;
}
int mrk[112345];

ll solve() {
	scanf("%d %s %s", &n, a, b);
	for(int i = 0; i < n; i++) mrk[i] = 0;
	int tot = 0;
	for(int i = 0; i < n; i++) {
		if(ty(i) == 2) tot += 2;
		else if (ty(i) == 1) continue;
		else if (ty(i) == 0) {
			if (ty(i - 1) == 1 && !mrk[i - 1]) {
				tot += 2;
				mrk[i - 1] = 1;
			} else if (ty(i + 1) == 1 && !mrk[i + 1]) {
				tot += 2;
				mrk[i + 1] = 1;
			} else tot += 1;
		}
	}
	return tot;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) printf("%lld\n", solve());
}

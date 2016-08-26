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
	scanf("%d %d", &n, &q);
	build(1, 0, n - 1);
	int bad = INT_MAX;
	for(i = 0; i < q; i++) {
		scanf("%d %d %d", &ql[i], &qr[i], &a[i]);
		ql[i]--; qr[i]--;
		if(get(1, 0, n - 1, ql[i], qr[i]) > a[i]) bad = min(bad, i);
		upd(1, 0, n - 1, ql[i], qr[i], a[i]);
	}

}

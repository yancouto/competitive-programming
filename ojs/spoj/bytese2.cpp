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

pii v[1123];
int main() {
	int i, n, l, r;
	for_tests(t, tt) {
		scanf("%d", &n);
		int vn = 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &l, &r);
			v[vn++] = pii(l, 1);
			v[vn++] = pii(r, -1);
		}
		sort(v, v + vn);
		int mx = 0;
		for(i = 0; i < vn; i++) {
			if(i) v[i].snd += v[i-1].snd;
			mx = max(mx, v[i].snd);
		}
		printf("%d\n", mx);
	}
}

// WA
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
const int MAX = 30009;
struct st {
	int x, i;
	bool operator < (st o) const { return x < o.x; }
} ww[MAX], hs[MAX];

int main() {
	int i, j, n, q, a, b;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n; i++) {
		scanf("%d", &ww[i].x);
		ww[i].i = i;
	}
	for(i = 0; i < n; i++) {
		scanf("%d", &hs[i].x);
		hs[i].i = i;
	}
	sort(hs, hs + n);
	sort(ww, ww + n);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		int ia, ib;
		for(j = 0; j < n; j++)
			if(hs[j].i == a)
				ia = j;
			else if(hs[j].i == b)
				ib = j;
		swap(hs[ia].i, hs[ib].i);
		ll tot = 0; int ant;
		for(j = n - 1; j >= 0; j--) {
			if(ww[j].i == hs[j].i) {
				if(j == 0) {
					tot += -ll(ant) * ll(ww[j + 1].x) + ll(ant) * ll(ww[j].x) + ll(ww[j + 1].x) * ll(hs[j].x);
				} else {
					tot += ll(ww[j].x) * ll(hs[j - 1].x) + ll(ww[j - 1].x) * ll(hs[j].x);
					ant = hs[j].x;
					j--;
				}
			} else {
				tot += ll(ww[j].x) * ll(hs[j].x);
				ant = hs[j].x;
			}
		}
		printf("%I64d\n", tot);
	}
}

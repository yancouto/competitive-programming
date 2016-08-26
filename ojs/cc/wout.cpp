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

int ac[1000009];
int main() {
	int n, h, i, l, r;
	for_tests(t, tt) {
		scanf("%d %d", &n, &h);
		for(i = 0; i < n; i++) ac[i] = 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &l, &r);
			ac[0]++; ac[l]--;
			ac[r + 1]++;
		}
		for(i = 1; i < n; i++)
			ac[i] += ac[i - 1];
		ll s = 0;
		for(i = 0; i < h; i++)
			s += ac[i];
		ll mns = s;
		for(i = h; i < n; i++) {
			s += ac[i] - ac[i - h];
			mns = min(s, mns);
		}
		printf("%lld\n", mns);
	}
	return 0;
}

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

int main() {
	int i, n, a1, b1, a2, b2, c1, d1, c2, d2;
	for_tests(t, tt) {
		scanf("%d", &n);
		int tot = 0;
		for(i = 0; i < n; i++) {
			scanf("%d:%d %d:%d | %d:%d %d:%d", &a1, &b1, &a2, &b2, &c1, &d1, &c2, &d2);
			int ab1 = a1 * 60 + b1, ab2 = a2 * 60 + b2;
			int cd1 = c1 * 60 + d1, cd2 = c2 * 60 + d2;
			if(abs( 8 * 60 - ab1) > 5) tot += ab1 - 8 * 60;
			if(abs(12 * 60 - ab2) > 5) tot += 12 * 60 - ab2;
			if(abs(14 * 60 - cd1) > 5) tot += cd1 - 14 * 60;
			if(abs(18 * 60 - cd2) > 5) tot += 18 * 60 - cd2;
		}
		printf("%c %02d:%02d\n", ((tot <= 0)? '+' : '-'), abs(tot) / 60, abs(tot) % 60);
	}
}

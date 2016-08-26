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

int a[14];
int main() {
	int i, s[2], j;
	while(scanf("%d %d", &s[0], &s[1]) != EOF) {
		int mx=  INT_MIN; s[1] = -s[1];
		for(i = 0; i < (1 << 12); i++) {
			for(j = 0; j < 12; j++) a[j] = s[!!(i & (1 << j))];
			int v = a[0] + a[1] + a[2] + a[3] + a[4];
			if(v >= 0) continue;
			for(j = 5; j < 12; j++) {
				v += a[j];
				v -= a[j - 5];
				if(v >= 0) break;
			}
			if(j < 12) continue;
			v = 0;
			for(j = 0; j < 12; j++) v += a[j];
			mx = max(mx, v);
		}
		if(mx < 0) puts("Deficit");
		else printf("%d\n", mx);
	}
}

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

int g[10009];
int main() {
	int n, a, i, c;
	while(true) {
		scanf("%d %d", &n, &a);
		if(!n) return 0;
		memset(g, 0, sizeof g);
		int tot = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &c);
			g[c - 1]++;
			tot += c;
		}
		if(tot == a) { puts(":D"); continue; }
		if(tot < a) { puts("-.-"); continue; }
		for(i = 10001; i >= 0; i--)
			g[i] += g[i + 1];
		int t = 0;
		for(i = 10001; ; i--) {
			t += g[i];
			if(t > a) {
				t -= g[i];
				int l = a - t;
				printf("%.4f\n", (i + 1 - double(l) / g[i]));
				break;
			}
		}
	}
}

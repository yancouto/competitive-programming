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

int s[105], a[105], b[105], k[105];
int main() {
	int i, j, n, m, x, y; char o;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		scanf("%d", &m);
		for(i = 0; i < m; i++) {
			scanf("%d %d %c%*c %d", &x, &y, &o, &k[i]);
			a[i] = x + y;
			b[i] = x - 1;
			if(o == 'g') { swap(a[i], b[i]); k[i] = -k[i]; }
			k[i]--;
		}
		s[0] = 0;
		for(i = 1; i <= n; i++) s[i] = 100000000;
		for(j = 0; j < n + 1; j++) {
			for(i = 0; i < m; i++)
				if(s[a[i]] > k[i] + s[b[i]])
					s[a[i]] = s[b[i]] + k[i];
		}
		for(i = 0; i < m; i++)
			if(s[a[i]] > k[i] + s[b[i]])
				break;
		if(i < m) puts("successful conspiracy");
		else puts("lamentable kingdom");
	}
}

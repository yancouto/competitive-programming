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

int a[100009];
int has[100009];
int main() {
	int i, s, e, c, n;
	while(true) {
		scanf("%d %d", &c, &n);
		if(!c) return 0;
		memset(has, 0, sizeof has);
		has[0] = 1;
		for(i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			a[i] = (a[i] + a[i - 1]) % c;
			if(has[a[i]]) {
				s = has[a[i]];
				e = i;
			}
			has[a[i]] = i + 1;
		}
		for(i = s; i <= e; i++)
			printf("%d ", i);
		putchar('\n');
	}
}

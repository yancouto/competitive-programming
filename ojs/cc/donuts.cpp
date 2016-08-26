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

int a[20009];
int main() {
	int i, j, n, m;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < m; i++)
			scanf("%d", &a[i]);
		sort(a, a + m);
		int tot = 0;
		for(i = 0; i < m - 1; i++) {
			while(i < m - 1 && a[i]) {
				a[i]--; tot++;
				a[m-2] += a[m-1]; m--;
			}
		}
		printf("%d\n", tot);
	}
}

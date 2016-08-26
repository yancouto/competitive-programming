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

int bit[1002 << 2][1002 << 2];
int get(int x, int yy) {
	int mx = 0;
	for(; x; x -= (x & -x))
		for(int y = yy; y; y -= (y & -y))
			mx = max(mx, bit[x][y]);
	return mx;
}

int sett(int x, int yy, int val) {
	for(; x < 1002; x += (x & -x))
		for(int y = yy; y < 1002; y += (y & -y))
			bit[x][y] = max(bit[x][y], val);
}
int x[100009], y[100009];

int main() {
	int i, n;
	for_tests(t, tt) {
		memset(bit, 0, sizeof bit);
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);
		int mx = 0;
		for(i = 0; i < n; i++) {
			int a = get(x[i], y[i]) + 1;
			mx = max(a, mx);
			sett(x[i], y[i], a);
		}
		printf("%d\n", mx);
	}
	return 0;
}

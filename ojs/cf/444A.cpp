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

int x[600];
int main() {
	int n, m, a, b, c, i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		scanf("%d", &x[i]);
	double mx = 0;
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		mx = max(mx, double(x[--a] + x[--b]) / double(c));
	}
	printf("%.15f\n", mx);
}

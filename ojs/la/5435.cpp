#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

inline int sq(int x) { return x * x; }

int r[1123];
double d[1123];
int main() {
	int i, j, n;
	while(scanf("%d", &n) != EOF) {
		double ans = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &r[i]);
			d[i] = r[i];
			for(j = 0; j < i; j++) {
				double D = sqrt(sq(r[i] + r[j]) - sq(r[i] - r[j]));
				d[i] = max(d[i], d[j] + D);
			}
			ans = max(ans, d[i] + r[i]);
		}
		printf("%.10f\n", ans);
	}
}

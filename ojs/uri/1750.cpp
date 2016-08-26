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
int a[1009];
int main() {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a + n);
	int mn = INT_MAX;
	for(i = 0; i < 2; i++) {
		int t = 0;
		for(j = 0; j < n / 2; j++) {
			int d = abs(a[(i+j*2)%n] - a[(i+j*2+1)%n]);
			t += min(d, 24 - d);
		}
		mn = min(mn, t);
	}
	printf("%d\n", mn);
}

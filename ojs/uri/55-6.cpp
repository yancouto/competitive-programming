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

int h[1003];
int main() {
	int n, i, k;
	while(scanf("%d %d", &n, &k) != EOF) {
		for(i = 0; i < n; i++)
			scanf("%d", &h[i]);
		if(n == 1) { puts("ugly"); continue; }
		if(h[1] < h[0]) { puts("beautiful"); continue; }
		int pic = 0, val = 0;
		for(i = 1; i < n - 1; i++) {
			if(h[i] > h[i-1] && h[i] > h[i+1]) pic++;
			if(h[i] < h[i-1] && h[i] < h[i+1]) val++;
		}
		if(pic == k && val == k - 1) puts("beautiful");
		else puts("ugly");
	}
	return 0;
}

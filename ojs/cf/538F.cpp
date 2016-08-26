// TLE
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

const int MAX = 200009;
int a[MAX], h[MAX];
inline int f(int ff, int k) { return (ff + k - 2) / k; }
int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(i = 2; i <= n; i++) {
		int x = 1;
		while(x < n) {
			int l = x, r = n - 1;
			if(x != n - 1 && f(i, x + 1) != f(i, x)) l = r = x;
			else if(x < n - 2 && f(i, x + 2) != f(i, x)) l = r = x + 1;
			while(l < r) {
				int m = (l + r + 1) / 2;
				if(f(i, m) < f(i, x)) r = m - 1;
				else l = m;
			}
			if(a[i] < a[f(i, x)]) { h[x]++; h[l+1]--; }
			x = r + 1;
		}
	}
	for(i = 1; i <= n - 1; i++) {
		h[i] += h[i - 1];
		printf("%d ", h[i]);
	}
	putchar('\n');
}

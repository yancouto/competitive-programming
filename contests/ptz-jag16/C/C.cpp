#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int a[1123]; char c[1123];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf(" %c %d", &c[i], &a[i]);
	int nb = 0;
	for(i = 0; i < n; i++) nb += (c[i] == 'y');
	int tot = 0;
	for(; nb > 0; tot++) {
		int m = -1;
		for(i = 0; i < n; i++)
			if(c[i] == 'y' && (m == -1 || a[i] < a[m]))
				m = i;
		assert(m != -1);
		for(i = m; i < n; i++) {
			if(c[i] == 'n' && a[i] >= a[m]) break;
			if(c[i] == 'y') nb--, c[i] = 'x';
		}
		for(i = m - 1; i >= 0; i--) {
			if(c[i] == 'n' && a[i] >= a[m]) break;
			if(c[i] == 'y') nb--, c[i] = 'x';
		}
	}
	printf("%d\n", tot);
}

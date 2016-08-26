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
int b, n, a[500009];
bool pos(int x) {
	int bi = b;
	for(int i = 0; i < n; i++)
		bi -= (a[i] + x - 1) / x;
	return bi >= 0;
}

int main() {
	while(true) {
		int x, i;
		scanf("%d %d", &n, &b);
		if(n == -1) return 0;
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		int l = 0, r = 5000009;
		while(l < r) {
			int m = (l + r) / 2;
			if(pos(m)) r = m;
			else l = m + 1;
		}
		printf("%d\n", l);
	}
}

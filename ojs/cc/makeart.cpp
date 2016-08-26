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

int a[112345];
int main() {
	int i, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		if(n < 3) { puts("No"); continue; }
		a[n] = a[n + 1] = a[n + 2] = -1;
		for(i = 0; i < n; i++)
			if(a[i] == a[i + 1] && a[i + 1] == a[i + 2])
				break;
		if(i < n) puts("Yes");
		else puts("No");
	}
}

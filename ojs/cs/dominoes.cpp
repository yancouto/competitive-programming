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

int a[2123456];

int main() {
	int i, j, n, k, x;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		a[x] = 1;
	}
	int choose = 0;
	i = j = 1;
	while(choose < k)
		choose += !a[j++];
	int mx = j - i;
	for(; i <= 1123456; ) {
		choose -= !a[i++];
		while(choose < k) choose += !a[j++];
		mx = max(mx, j - i);
	}
	printf("%d\n", mx);
}

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

int main() {
	int a[3];
	while(scanf("%d %d %d", &a[0], &a[1], &a[2]) != EOF && a[0]) {
		sort(a, a + 3);
		if(a[0] == a[2]) {
			if(a[0] == 13) puts("*");
			else printf("%d %d %d\n", a[0] + 1, a[0] + 1, a[0] + 1);
		} else if(a[0] == a[1]) {
			if(a[2] == 13) printf("1 %d %d\n", a[0] + 1, a[0] + 1);
			else printf("%d %d %d\n", a[0], a[1], a[2] + 1);
		} else if(a[1] == a[2]) {
			int nx = a[0] + 1;
			if(a[0] + 1 == a[1]) {
				if(a[1] == 13) puts("1 1 1");
				else printf("%d %d %d\n", a[1], a[2], a[1] + 1);
			} else printf("%d %d %d\n", a[0] + 1, a[1], a[2]);
		} else puts("1 1 2");
	}
}

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
	int n, k, p;
	scanf("%d %d %d", &n, &k, &p);
	if(p == 100) {
		printf("1\n0 1");
		for(int i = 2; i < n; i++)
			printf(" 0");
		putchar('\n');
	} else if(p >= 50) puts("0");
	else {
		for(int wi = 1; wi <= k; wi++) {
			if((wi * 50) % (50 - p)) continue;
			int all = (wi * 50) / (50 - p);
			if(all - wi >= 0 && all - wi <= (n - 1) * k) {
				printf("1\n%d", wi);
				all -= wi;
				for(int i = 1; i < n; i++) {
					printf(" %d", min(all, k));
					all -= min(all, k);
				}
				putchar('\n');
				return 0;
			}
		}
		printf("0\n");
	}
}

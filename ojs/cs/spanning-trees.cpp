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

int main() {
	int i, n, k;
	scanf("%d %d", &n, &k);
	if(k == 0) {
		if(n == 1) {
			puts("0");
		} else if(n >= 2 && n <= 3) {
			puts("-1");
		} else {
			// TODO
			printf("%d\n", 2 * (n - 1));
			for(i = 0; i < n - 1; i++)
				printf("%d %d 1\n", i + 1, i + 2);
			for(i = 2; i + 2 <= n; i += 2)
				printf("%d %d 2\n", i, i + 2);
			printf("%d %d 2\n", i, 1);
			for(i = 1; i + 2 <= n; i += 2)
				printf("%d %d 2\n", i, i + 2);
		}
		return 0;
	}
	int r = n - (k + 1);
	printf("%d\n", 2 * r + k);
	puts("1 2 3");
	for(i = 0; i < r; i++) {
		printf("1 %d 2\n", 3 + i);
		printf("%d %d 5\n", 3 + i, 2 + i);
	}
	if(k > 1) printf("1 %d 1\n", n);
	for(i = 0; i < k - 2; i++)
		printf("%d %d 1\n", n - i, n - i - 1);
}

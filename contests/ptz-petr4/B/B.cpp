#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int main () {
#ifdef ONLINE_JUDGE
	freopen("beautifulgraph.in", "r", stdin);
	freopen("beautifulgraph.out", "w", stdout);
#endif
	int i, n;
	scanf("%d", &n);
	if(n == 1) {
		puts("1 0");
	} else if(n == 2) {
		puts("2 1\n1 2");
	} else if(n == 3) {
		puts("3 3\n1 2\n2 3\n1 3");
	} else {
		printf("%d %d\n", n, 2 * (n - 2));
		for(i = 3; i <= n; i++)
			printf("%d %d\n%d %d\n", 1, i, i, 2);
	}
}


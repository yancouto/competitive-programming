#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;
const int N= 50007;

int t, n, i, a[N];

int f (int x, int y) {
	if (x > y) return 0;
	if (a[x] != a[x+1] && a[x] != a[y]) return true;
	if (a[y] != a[y-1] && a[x] != a[y]) return true;
	if (a[x] == a[x+1]) return f(x+2,y);
	if (a[y-1] == a[y]) return f(x,y-2);
	if (a[x] == a[y]) return f(x+1,y-1);
	return 1;
}

int main () {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		int cnt = 0;
		for(i = 30; i >= 0; i--) {
			cnt = 0;
			for (int j = 0; j < n; j++)
				if (a[j]&(1<<i)) cnt++;
			if (cnt&1) break;
		}
		if (i < 0) {
			printf("Draw\n");
			continue;
		}
		for (int j = 0; j < n; j++)
			a[j] = !!(a[j]&(1<<i));
		if ((n&1) == 0) {
			printf("First\n");
		} else if (cnt%4 == 3) {
			printf("Second\n");
		} else {
			int x = 0;
			if (a[0]) x = (x | (!f(1,n-1)));
			if (a[n-1]) x = (x | (!f(0,n-2)));

			if (x == 1) printf("First\n");
			else printf("Second\n");
		}
	}
}

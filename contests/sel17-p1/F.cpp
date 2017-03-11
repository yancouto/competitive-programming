#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N = 212345;
int a[N];

int main() {
	int i, t, n, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &k);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		sort(a, a + n);
		int mn = INT_MAX;
		for(i = 0; i <= n - k; i++)
			mn = min(mn, a[i + k - 1] - a[i]);
		printf("%d\n", mn);
	}
}

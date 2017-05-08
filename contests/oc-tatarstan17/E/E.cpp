#include <bits/stdc++.h>
using namespace std;


int main() {
	int n, k;
	scanf("%d %d", &n, &k); n--;
	int x = (k / n), i;
	int tot = 0;
	for(i = 0; i < n; i++) {
		int y = x + (i < (k % n));
		tot += (y * (y - 1)) + y;
	}
	printf("%d\n", tot);
}

#include <bits/stdc++.h>
using namespace std;
int a[200], tot, k;


int main() {
	int i;
	scanf("%d", &k);
	for(i = 0; i < k; i++) {
		scanf("%d", &a[i]);
		tot += a[i];
	}
	sort(a, a + k);
	int g = 0;
	for(i = 0; 2 * i <= k; i++)
		g += a[i] / 2 + 1;
	printf("%d\n", g);
}

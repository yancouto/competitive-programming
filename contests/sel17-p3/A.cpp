#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int s[5];
int a[5][5123];
int b[5123 * 5123];

int main() {
	int i, j, l;
	while(scanf("%d %d %d %d %d", &l, &s[0], &s[1], &s[2], &s[3]) != EOF && l) {
		for(j = 0; j < 4; j++)
			for(i = 0; i < s[j]; i++)
				scanf("%d", &a[j][i]);
		for(i = 0; i < s[2]; i++)
			for(j = 0; j < s[3]; j++)
				b[i * s[3] + j] = a[2][i] + a[3][j];
		sort(b, b + s[2] * s[3]);
		ll tot = 0;
		for(i = 0; i < s[0]; i++)
			for(j = 0; j < s[1]; j++)
				tot += (upper_bound(b, b + s[2] * s[3], l - a[0][i] - a[1][j]) - b);
		printf("%lld\n", tot);
	}
}

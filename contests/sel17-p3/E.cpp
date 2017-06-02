#include <bits/stdc++.h>
using namespace std;

int pr[50][112345];

int main() {
	int n;
	for(n = 0; n <= 100000; n++) {
		int x = n, sum = 0;
		while(x) sum += (x % 10), x /= 10;
		pr[sum][n] = n;
	}
	for(int i = 0; i <= 45; i++)
		for(n = 1; n <= 100000; n++)
			if(pr[i][n] == 0)
				pr[i][n] = pr[i][n - 1];
	while(scanf("%d", &n) == 1) {
		int sum = 0, x = n;
		while(n) sum += (n % 10), n /= 10;
		printf("%d\n", pr[sum - 1][x]);
	}
}

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n, i, d;
	int sum = 0, mn = 10000;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &d);
		mn = min(mn, d);
		sum += d;
	}
	printf("%s\n", (mn >= 1 && (sum == 2 * (n - 1)))? "Yes" : "No");
	return 0;
}
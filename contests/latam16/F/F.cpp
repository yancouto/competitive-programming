#include <bits/stdc++.h>
using namespace std;

int main() {
	int i, n, c, s, x;
	scanf("%d %d %d", &n, &c, &s);
	int cur = 1;
	int tot = (s == 1);
	for(i = 0; i < c; i++) {
		scanf("%d", &x);
		cur += x;
		if(cur > n) cur = 1;
		else if(cur == 0) cur = n;
		tot += (cur == s);
	}
	printf("%d\n", tot);
}

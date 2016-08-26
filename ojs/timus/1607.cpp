#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, b, c, d;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	c += d;
	while(true) {
		c -= d;
		if(a >= c) { printf("%d\n", a); return 0; }
		a += b;
		if(a >= c) { printf("%d\n", c); return 0; }
	}
}

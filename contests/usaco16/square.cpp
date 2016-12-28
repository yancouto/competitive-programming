#include <bits/stdc++.h>
using namespace std;

int sqr(int x) { return x * x; }

int main() {
	freopen("square.in", "r", stdin);
	freopen("square.out", "w", stdout);
	int x1, x2, y1, y2, z1, z2, w1, w2;
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	scanf("%d %d %d %d", &z1, &w1, &z2, &w2);
	x1 = min(x1, z1);
	x2 = max(x2, z2);
	y1 = min(y1, w1);
	y2 = max(y2, w2);
	printf("%d\n", sqr(max(x2 - x1, y2 - y1)));
}

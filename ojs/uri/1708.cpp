#include <cstdio>

int main() {
	int x, y;
	scanf("%d %d", &x, &y);
	printf("%d\n", (((x*y + y - x - 1)/(y-x)) - 1) / x + 1);
	return 0;
}

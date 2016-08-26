#include <cstdio>
#include <cmath>

int main() {
	double x, A, B, C, a, b, c, sq3 = sqrt(3.);
	while(scanf("%lf", &x) != EOF) {
		A = (M_PI / 2. - 1.) * x * x;
		B = (M_PI / 3. - sq3 / 4.) * x * x;
		C = x * x;
		c = B - A;
		b = (C - A - 4*c) / 2;
		a = A - 2 * b;
		printf("%.3f %.3f %.3f\n", a, 4 * b, 4 * c);
	}
	return 0;
}

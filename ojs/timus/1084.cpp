#include <bits/stdc++.h>
using namespace std;
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const double sq2 = sqrt(2), eps = 1e-8, pi = acos(-1);
int main() {
	double l, r;
	scanf("%lf %lf", &l, &r);
	if(r - sq2 * l / 2. > eps) {
		printf("%.3f\n", l * l);
	} else if(r - l / 2.> eps) {
		double x = sqrt(4. * r * r - l * l);
		double s = x * l / (2. * r * r);
		double ex = asin(s) / (2. * pi) * pi * r * r - x * l / 4.;
		printf("%.3f\n", pi * r * r -  4. * ex);
	} else {
		printf("%.3f\n", pi * r * r);
	}
}

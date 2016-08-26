#include <bits/stdc++.h>
using namespace std;

double x[103], y[103];

double dist(int i, int j) {
	return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] -y[j]) * (y[i] - y[j]));
}

const double pi_ = 3.141592653589793;

int main() {
	int i, n;
	double r;
	scanf("%d %lf", &n, &r);
	double d = 0;
	for(i = 0; i < n; i++)
		scanf("%lf %lf", &x[i], &y[i]);
	for(i = 0; i < n; i++)
		d += dist(i, (i + 1) % n);
	printf("%.2f\n", d + 2 * pi_ * r);
}

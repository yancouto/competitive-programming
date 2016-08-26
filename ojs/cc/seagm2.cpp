#include <cstdio>
#include <cmath>

struct num {
	long double d;
	int b;
	void deb() {
		printf("%.3Lf*10^(%d)\n", d, b);
	}
};

num ps[15];
void mult(num &n, long double d) {
	n.d *= d;
	while(n.d > 0 && n.d < 1) {
		n.d *= 10;
		n.b--;
	}
}

num add(num n, num n2) {
	if(n2.d == 0) return n;
	if(n.d == 0) return n2;
	if(n.b < n2.b) return add(n2, n);
	if(n.b > n2.b + 8) return n;
	while(n2.b < n.b) {
		n2.b++;
		n2.d /= 10;
	}
	n.d += n2.d;
	while(n.d > 0 && n.d < 1) {
		n.d *= 10;
		n.b--;
	}
	return n;
}

int main() {
	int t, i, j; double d;
	scanf("%d", &t);
	while(t--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) {
			ps[i].d = 1;
			ps[i].b = 0;
			for(j = 0; j < m; j++) {
				scanf("%lf", &d);
				mult(ps[i], d);
			}
			if(i > 0)
				ps[i] = add(ps[i], ps[i - 1]);
		}
		ps[0].d /= ps[n - 1].d;
		ps[0].b -= ps[n - 1].b;
		while(ps[0].b > 0) {
			ps[0].b--;
			ps[0].d *= 10.;
		}
		while(ps[0].b < 0) {
			ps[0].b++;
			ps[0].d /= 10.;
		}
		printf("%.6Lf\n", ps[0].d);
	}
	return 0;
}

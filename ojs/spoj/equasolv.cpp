#include <bits/stdc++.h>
using namespace std;

const int N = 109;

double a[N][N];
double ans[N];

void solve(int n) {
	for(int i = 0; i < n; i++) {
		int mx = i;
		for(int j = i + 1; j < n; j++)
			if(abs(a[j][i]) > abs(a[mx][i]))
				mx = j;
		swap_ranges(a[i], a[i] + n + 1, a[mx]);
		if(abs(a[i][i]) < 1e-6) /* sem solucao*/;
		for(int j = i + 1; j < n; j++) {
			for(int k = i + 1; k <= n; k++)
				a[j][k] -= (a[j][i] / a[i][i]) * a[i][k];
			a[j][i] = 0;
		}
	}
	for(int i = n - 1; i >= 0; i--) {
		ans[i] = a[i][n];
		for(int j = i + 1; j < n; j++)
			ans[i] -= a[i][j] * ans[j];
		ans[i] /= a[i][i];
	}
}

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n + 1; j++)
			scanf("%lf", &a[i][j]);
	solve(n);
	for(i = 0; i < n; i++) {
		if(abs(ans[i]) < 5e-6) ans[i] = abs(ans[i]);
		printf("%.5f\n", ans[i]);
	}
}

const int N = ;

double a[N][N];
double ans[N];

// sum(a[i][j] * x_j) = a[i][n] para 0 <= i < n
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

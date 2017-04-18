#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef unsigned long long int ll;

const int N = 6e3+7;

ll w[N][N];
ll a[2][N];
ll h[N];
ll ac[N];
ll pd[N][N];
int opt[N][N];
int n;
ll b, c;

int main () {
	while(true) {
	scanf("%d %llu %llu", &n, &b, &c);
	if(feof(stdin)) return 0;

	for (int i = 1; i <= n; i++) {
		scanf("%llu", &h[i]);
		ac[i] = ac[i-1] + h[i];
		w[i][i] = h[i];
	}

	for (int i = 0; i <= n; i++) {
		for (int j = i+1; j <= n; j++) {
			w[i][j] = w[i][j-1] + ac[j] - ac[(i+j+1)/2 - 1];
		}
	}

	for (int i = 0; i <= n; i++)
		opt[n+1][i] = i;

	a[0][n] = a[1][n] = 0;
	for (int i = 1; i <= n; i++)
		a[0][i] = a[0][i-1] + ac[i];
	for (int i = n; i >= 1; i--)
		a[1][i] = a[1][i+1] + ac[n] - ac[i];

	for (int d = 0; d < n; d++) {
		for (int i = d; i <= n; i++) {
			int k = i-d;
			if (k <= 0) continue;

			if (d == 0) {
				opt[k][i] = i;
				pd[k][i] = 0;
			} else {
				opt[k][i] = i;
				pd[k][i] = ULLONG_MAX;
				for (int j = max(opt[k][i-1],k); j <= i && j <= opt[k+1][i]; j++) {
				//for (int j = k; j <= i; j++) {
					ll loc;
					if (i == n && k == 1) {
						loc = a[1][j] + a[0][j-1];
					} else if (i == n) {
						loc = a[1][j] + pd[k-1][j-1];
					} else if (k == 1) {
						loc = w[j+1][i] + a[0][j-1];
					} else {
						loc = w[j+1][i] + pd[k-1][j-1];
					}

					if (loc < pd[k][i]) {
						opt[k][i] = j;
						pd[k][i] = loc;
					}
				}
				assert(opt[k][i] >= opt[k][i-1]);
				assert(opt[k][i] <= opt[k+1][i]);
			}


			//printf("%d %d : %llu\n", k, i, pd[k][i]);
		}
	}

	for (int k = 1; k <= n; k++)  {
		if (k > 1)
			printf(" ");
		printf("%llu", pd[k][n]*c + ll(b)*k);
	}
	printf("\n");
	}
}

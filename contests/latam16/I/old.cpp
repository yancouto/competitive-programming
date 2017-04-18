#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef unsigned long long int ll;

const int N = 6e3+7;

ll w[N][N];
ll a[2][N];
ll h[N];
ll ac[N];
int n;
ll b, c;

void dc (int i, int j, int l, int r, bool t) {
	if (i > j) return;
	int k = (i+j)/2;
	int mn = k;

	a[t][k] = a[!t][k-1];
	for (int p = min(r,k-1); p >= l; p--) {
		if (a[!t][p-1] + w[p+1][k] < a[t][k]) {
			a[t][k] = a[!t][p-1] + w[p+1][k];
			mn = p;
		}
	}

	if (i == j) return;
	dc(i,k-1,l,mn,t);
	dc(k+1,j,mn,r,t);
}

int main () {
	scanf("%d %llu %llu", &n, &b, &c);

	for (int i = 1; i <= n; i++) {
		scanf("%llu", &h[i]);
		ac[i] = ac[i-1] + h[i];
		w[i][i] = h[i];
	}

	for (int i = 0; i <= n; i++)
		for (int j = i+1; j <= n; j++)
			w[i][j] = w[i][j-1] + ac[j] - ac[(i+j+1)/2 - 1];
	
	for (int i = 1; i <= n; i++)
		a[0][i] = a[0][i-1] + ac[i];

	for (int k = 1; k < n; k++) {
		ll mn = a[!(k&1)][n];
		ll sm = 0;

		for (int i = n; i > 0; i--) {
			sm += ac[n] - ac[i];
			mn = min(mn, a[!(k&1)][i-1] + sm);
		}
		printf("%llu ", mn*c + b*ll(k));

		if (k == n-1) break;
		
		dc(1, n, 1, n, k&1);
	}

	printf("%llu\n", ll(n)*b);
}

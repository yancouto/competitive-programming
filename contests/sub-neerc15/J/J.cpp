#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double cood;

const int N = 1e4+7;

ll w[N][2];
ll p[3][2];
ll k, v;
int n;
ll m[2], c[2];

int main () {
#ifdef ONLINE_JUDGE
	freopen("joy.in", "r", stdin);
	freopen("joy.out", "w", stdout);
#endif
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			scanf("%lld", &p[i][j]);

	scanf("%d %lld %lld", &n, &k, &v);

	for (int j = 0; j < 2; j++)
		p[2][j] = p[0][j];

	int j = 0;
	ll nx;

	scanf("%lld", &nx);

	for (int i = 0; i < k; i++) {
		for (int z = 0; z < 2; z++)
			w[i][z] = w[i-!!i][z];
		if (j < n && nx == i) {
			scanf("%lld %lld", &w[i][0], &w[i][1]);
			scanf("%lld", &nx);
			j++;
		}
		for (int z = 0; z < 2; z++)
			p[2][z] += w[i][z];
	}

	for (int j = 0; j < 2; j++) {
		m[j] = p[1][j] - p[2][j];
		c[j] = p[0][j]*k;
	}

	if (m[0]*m[0] + m[1]*m[1] > v*v*k*k) {
		printf("No\n");
		return 0;
	}

	printf("Yes\n");

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 2; j++)
			c[j] += m[j] + w[i][j]*k;
		printf("%.20f %.20f\n", double(c[0])/double(k), double(c[1])/double(k));
	}
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll tr[112][112][112], lo[112][112][112];
int n;

void add(int i, int x, int y, int a) {
	tr[i][x + a - 1][y]++;
	tr[i][x + a - 1][y + a]--;
	lo[i][x - 1][y]--;
	lo[i][x + a - 1][y + a]++;
}

int A[112][112][112];

void accumulate(int i) {
	for(int x = 1; x <= 100; x++)
		for(int y = 1; y <= 100; y++)
			tr[i][x][y] += tr[i][x][y - 1];
	for(int y = 1; y <= 100; y++)
		for(int x = 100; x >= 1; x--)
			tr[i][x][y] += tr[i][x + 1][y];
	for(int y = 1; y <= 100; y++)
		for(int x = 1; x <= 100; x++)
			lo[i][x][y] += lo[i][x - 1][y - 1];
	for(int y = 1; y <= 100; y++)
		for(int x = 100; x >= 1; x--)
			lo[i][x][y] += lo[i][x + 1][y];
	// accumulated
	for(int x = 1; x <= 100; x++)
		for(int y = 1; y <= 100; y++)
			A[i][x][y] = tr[i][x][y] + lo[i][x][y];

	//printf("i %d\n", i);
	//for(int x = 1; x <= i; x++)
	//	for(int y = 1; y <= x; y++)
	//		printf("%d%c", A[i][x][y], " \n"[y == x]);
	//puts("-------");

	for(int x = 0; x <= 100; x++)
		for(int y = 0; y <= 100; y++)
			tr[i][x][y] = lo[i][x][y] = A[i][x][y];
	//
	for(int y = 1; y <= 100; y++)
		for(int x = 1; x <= 100; x++)
			tr[i][x][y] += tr[i][x - 1][y];
	for(int x = 1; x <= 100; x++)
		for(int y = 100; y >= 1; y--)
			tr[i][x][y] += tr[i][x][y + 1];
	for(int y = 1; y <= 100; y++)
		for(int x = 1; x <= 100; x++)
			lo[i][x][y] += lo[i][x - 1][y - 1];
	for(int y = 1; y <= 100; y++)
		for(int x = 1; x <= 100; x++)
			lo[i][x][y] += lo[i][x - 1][y];

	//for(int x = 1; x <= i; x++)
	//	for(int y = 1; y <= x; y++)
	//		printf("%d%c", tr[i][x][y], " \n"[y == x]);
	//puts("=======");
	//for(int x = 1; x <= i; x++)
	//	for(int y = 1; y <= x; y++)
	//		printf("%d%c", lo[i][x][y], " \n"[y == x]);
	//puts("XXXXX");
}

ll ans(int i, int x, int y, int a) {
	ll ret =
		+ tr[i][x + a - 1][y]
		- tr[i][x + a - 1][y + a]
		- lo[i][x + a - 2][y + a - 1];
	if(x > 1)
		ret += lo[i][x - 2][y - 1];
	return ret;
}

int main () {
	int m, q;
	scanf("%d %d %d", &n, &m, &q);
	int x, y, z, a, i;
	for(i = 0; i < m; i++) {
		scanf("%d %d %d %d", &x, &y, &z, &a);
		for(int xx = x; xx < x + a; xx++)
			add(xx, y, z, (xx - x) + 1);
	}
	for(int xx = 1; xx <= n; xx++)
		accumulate(xx);
	for(i = 0; i < q; i++) {
		scanf("%d %d %d %d", &x, &y, &z, &a);
		ll r = 0;
		for(int xx = x; xx < x + a; xx++)
			r += ans(xx, y, z, (xx - x) + 1);
		printf("%lld\n", r);
	}
}

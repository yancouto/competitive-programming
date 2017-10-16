#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int K = 12;

int memo[(1<<10)][K][K];
pii play[(1<<10)][K][K];
int dif[K][K];
char str[K];
int n, m, k;

int pd (int mask, int i, int j) {
	if (__builtin_popcount(mask) == 1)
		return 0;

	int & me = memo[mask][i][j];
	if (me != -1) return me;
	me = INT_MAX;

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			if ((dif[x][y]&mask) != 0 && (dif[x][y]&mask) != mask) {
				int loc = max(pd(dif[x][y]&mask, x, y), pd(mask - (dif[x][y]&mask), x, y)) + abs(x-i) + abs(y-j);
				if (loc < me) {
					me = loc;
					play[mask][i][j] = pii(x,y);
				}
			}
		}
	}
	
	return me;
}

void walk (int i, int j, int x, int y) {
	while (i != x) {
		if (i < x) {
			printf("D");
			i++;
		} else { 
			printf("U");
			i--;
		}
	}

	while (j != y) {
		if (j < y) {
			printf("R");
			j++;
		} else {
			printf("L");
			j--;
		}
	}
}

int which (int mask) {
	int r = 0;
	while (mask != 1) {
		mask /= 2;
		r++;
	}
	return r;
}

void build (int mask, int i, int j) {
	if (__builtin_popcount(mask) == 1) {
		printf("%d", which(mask));
		return;
	}

	pii tar = play[mask][i][j];
	walk(i,j,tar.first,tar.second);
	i = tar.first;
	j = tar.second;

	printf("(");
	build(mask&dif[i][j], i, j);
	printf(":");
	build(mask - (mask&dif[i][j]), i, j);
	printf(")");
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("image.in", "r", stdin);
	freopen("image.out", "w", stdout);
#endif

	scanf("%d %d %d", &k, &n, &m);
	for (int c = 0; c < k; c++) {
		for (int i = 0; i < n; i++) {
			scanf(" %s", str);

			for (int j = 0; j < m; j++) {
				if (str[j] == 'W')
					dif[i][j] |= (1<<c);
			}
		}
	}

	memset(memo, -1, sizeof memo);
	pd((1<<k) - 1, 0, 0);
	build((1<<k) - 1, 0, 0);
	printf("\n");
}


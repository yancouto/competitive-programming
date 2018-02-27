#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int a[312][312];
int bk[312][312];

void prn(int n, int m) {
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++)
			putchar(a[i][j]? '#' : '.');
		putchar('\n');
	}
}

int main() {
	int i, j, n, m;
	scanf("%d %d", &m, &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			char c;
			scanf(" %c", &c);
			a[i][j] = (c == '#');
		}
	while(true) {
		printf("n %d m %d\n", n, m);
		bool has = true;
		bool bad = false;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				bk[i][j] = a[i][j];
		if(n <= 2 || m <= 2) break;
		prn(n, m);
		puts("--------");
		for(i = 0; i < n - 2; i++) {
			for(j = 0; j < m - 2; j++)
				if(a[i][j]) {
					printf("ping %d, %d\n", i, j);
					for(int di = 0; di < 3; di++)
						for(int dj = 0; dj < 3; dj++)
							a[i + di][j + dj] ^= 1;
					a[i][j] = 1;
					prn(n, m);
				}
			if(a[i][m - 2] && a[i][m - 1]) {
				printf("badfull at %d\n", i);
				bad = !has;
				has = false;
				for(int di = 0; di < 3; di++)
					for(int dj = 0; dj < 3; dj++)
						a[i + di][m - 3 + dj] ^= 1;
			} else if(a[i][m - 2] || a[i][m - 1]) {
				printf("badat %d\n", i);
				bad = !has;
				has = false;
			}
		}
		for(i = n - 2; i < n; i++)
			for(j = 0; j < m; j++)
				if(a[i][j]) {
					printf("badlast at %d, %d\n", i, j);
					bad = !has;
					has = false;
				}
		if(bad) break;
		n -= 2;
		m -= 2;
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++)
			putchar(bk[i][j]? '#' : '.');
		putchar('\n');
	}
}

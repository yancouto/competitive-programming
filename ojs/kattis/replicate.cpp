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

int oi = 50, oj = 50;

int a[100][200][200];

int main() {
	a[0][oi][oj] = 1;
	int i, j;
	for(int t = 0; t < 50; t++) {
		printf("t = %d\n\n", t);
		for(i = oi - t; i <= oi + t; i++) {
			for(j = oj - t; j <= oj + t; j++)
				putchar(a[t][i][j]? '1' : ' ');
			putchar('\n');
		}
		puts("\n=======\n");
		for(i = oi - t - 1; i <= oi + t + 1; i++)
			for(j = oj - t - 1; j <= oj + t + 1; j++) {
				a[t + 1][i][j] = 0;
				for(int di = -1; di <= 1; di++)
					for(int dj = -1; dj <= 1; dj++)
						if(di || dj)
							a[t + 1][i][j] ^= a[t][i + di][j + dj];
			}
	}
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1e3+7;

int n;
char str[N][N];
bitset<N> mat[N];
int adj[N][N];
bool ok;

bool testa () {
	int cn = 0;

	for (int i = 0; i < n; i++)

	ok = 1;
	return 1;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("avia.in", "r", stdin);
	freopen("avia.out", "w", stdout);
#endif
	scanf("%d", &n);
	srand(time(NULL));

	for(int i = 0; i < n; i++) scanf(" %s", str[i]);

	int k = 64;
	do {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (str[i][j] == '+') {
					int a = min(i,j);
					int b = max(i,j);
					if (mat[a][b] == 0)
						mat[a][b] = 1+(rand()%2);
				}
			}
		}
	} while (!testa());

	if (!ok)
		printf("Impossible\n");
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int a = min(i,j);
				int b = max(i,j);
				if (str[i][j] == '-')
					putchar(str[i][j]);
				else
					putchar('0'+mat[a][b]);
			}
			putchar('\n');
		}
	}
}

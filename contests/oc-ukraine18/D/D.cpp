#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 203;

int n, m, k;
char mat[N][N];
vector<int> res[2];

void fail () {
	printf("NO\n");
	exit(0);
}

int main () {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < n; i++) {
		scanf(" %s", mat[i]);
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cnt += (mat[i][j] == '1');
		if (cnt == k) { res[0].pb(i); cnt = 0; }
		if (cnt > k) fail();
	}
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++)
			cnt += (mat[i][j] == '1');
		if (cnt == k) { res[1].pb(j); cnt = 0; }
		if (cnt > k) fail();
	}
	printf("YES\n");
	for (int x = 0; x < 2; x++) {
		for (int i = 0; i < k-1; i++)
			printf("%d ", res[x][i]+1);
		printf("\n");
	}
}

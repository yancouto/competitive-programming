#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 503;
const int T = 1e6+3;

int n, m;
int mat[N][N];
ll lm[T][4];
int ls[T];

int main () {
	scanf("%d %d", &n, &m);
	memset(lm, -1, sizeof lm);

	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < m; j++) {
			int a;
			scanf("%d", &a);
			a++;
			mat[i][j] = a;
			if (lm[a][0] == -1) {
				lm[a][0] = lm[a][1] = i;
				lm[a][2] = lm[a][3] = j;
			} else {
				lm[a][0] = min(lm[a][0],i);
				lm[a][1] = max(lm[a][1],i);
				lm[a][2] = min(lm[a][2],j);
				lm[a][3] = max(lm[a][3],j);
			}
			int t = a;
		}
	}

	int res = 0;
	for (int t = 1; t < T; t++) {
		if (lm[t][0] == -1) continue;
		//cout << t << " " << lm[t][0] << " " << lm[t][1] << " and " << lm[t][2] << " " << lm[t][3] << endl;
		for (ll i = lm[t][0]; i <= lm[t][1]; i++) {
			for (ll j = lm[t][2]; j <= lm[t][3]; j++) {
				int a = mat[i][j];
				if (a == t || ls[a] == t) continue;
				ls[a] = t;
				if (lm[t][0] <= lm[a][0] && lm[t][1] >= lm[a][1] && lm[t][2] <= lm[a][2] && lm[t][3] >= lm[a][3]) {
					//cout << t << " has " << a << endl;
					res++;
				}
			}
		}
	}
	printf("%d\n", res);
}

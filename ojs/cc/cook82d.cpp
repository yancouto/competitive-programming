#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

const int N = 1123456;

const int K = 6;
int p[K][N], acc[K][N], v[K][N];

int main() {
	int i, k, n, m, q, a, b;
	scanf("%d %d", &n, &m);
	for(k = 0; k < K; k++)
		for(i = 1; i <= m; i++)
			p[k][i] = i;
	for(k = 0; k < K; k++) random_shuffle(p[k] + 1, p[k] + m + 1);
	for(i = 1; i <= m; i++) {
		scanf("%d %d", &a, &b);
		for(k = 0; k < K; k++)
			v[k][i] = p[k][a] ^ p[k][b];
	}
	for(k = 0; k < K; k++)
		for(i = 1; i <= m; i++)
			acc[k][i] = acc[k][i - 1] ^ v[k][i];
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &a, &b);
		for(k = 0; k < K; k++)
			if(acc[k][b] ^ acc[k][a - 1])
				break;
		if(k < K) puts("No");
		else puts("Yes");
	}
}

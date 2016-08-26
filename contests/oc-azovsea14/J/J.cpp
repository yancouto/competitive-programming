#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 1123, M = 1123;

void imp() {
	puts("FAIL");
	exit(0);
}

char s[N][M];
int z[N][M];
int p[N], cur[N], ans[N][2], init[N];

int main() {
	int i, n, k, Q, j, q;
	scanf("%d %d %d", &n, &k, &Q);
	for(i = 0; i < n; i++) {
		scanf("%s", s[i]);
		z[i][Q - 1] = s[i][Q - 1] - '0';
		for(j = Q - 2; j >= 0; j--)
			z[i][j] = (s[i][j] == '0'? 0 : 1 + z[i][j + 1]);
	}
	if(k == n) {
		for(i = 0; i < n; i++) if(z[i][0] != Q) imp();
		printf("WIN\n");
		for(i = 0; i < n; i++) printf("%d ", i + 1);
		printf("\n0\n");
		return 0;
	}
	for(i = 0; i < n; i++)
		p[i] = i;
	sort(p, p + n, [](int i, int j) { return z[i][0] > z[j][0]; });
	if(z[p[k-1]][0] == 0) imp();
	for(i = 0; i < k; i++) init[i] = cur[i] = p[i];
	for(i = k; i < n; i++) p[i - k] = p[i];
	for(q = 1; q < Q; q++) {
		sort(cur, cur + k, [q](int i, int j) { return z[i][q] < z[j][q]; });
		sort(p, p + n - k, [q](int i, int j) { return z[i][q] > z[j][q]; });
		if(z[p[0]][q] > z[cur[0]][q]) {
			ans[q][0] = cur[0];
			ans[q][1] = p[0];
			swap(cur[0], p[0]);
		}
		for(i = 0; i < k; i++)
			if(z[cur[i]][q] == 0)
				imp();
	}
	printf("WIN\n");
	for(i = 0; i < k; i++) printf("%d ", init[i] + 1);
	int ct = 0;
	for(i = 1; i < Q; i++) ct += (ans[i][0] != ans[i][1]);
	printf("\n%d\n", ct);
	for(i = 1; i < Q; i++) {
		if(ans[i][0] == ans[i][1]) continue;
		printf("%d %d %d\n", i, ans[i][0] + 1, ans[i][1] + 1);
	}
}

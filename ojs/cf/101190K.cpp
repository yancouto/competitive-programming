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

const int N = 3123;

bool h1[N][N], h2[N][N], h3[N][N];
bool A[N][N];
int d = 1009;

#define i first
#define j second

pii read(bool h[N][N]) {
	int n, m;
	scanf("%d %d", &n, &m);
	char c;
	pii mn(-1, -1);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			scanf(" %c", &c);
			h[i + d][j + d] = (c == '*');
			if(c == '*' && mn.i == -1)
				mn = pii(i + d, j + d);
		}
	return mn;
}

int ni, nj;
int oi, oj;

bool test(int di, int dj, bool h1[N][N], bool h2[N][N], bool h3[N][N], pii mn3) {
	//printf("=== TEST(%d, %d) ===\n", di, dj);
	di = -di;
	dj = -dj;
	oi = di, oj = dj;
	pii mn(-1, -1);
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++) {
			A[i][j] = h1[i][j];
			if(i + di >= 0 && i + di < N && j + dj >= 0 && j + dj < N && h2[i + di][j + dj])
				A[i][j] = !A[i][j];
			if(A[i][j] && mn.i == -1) mn = pii(i, j);
			//if(A[i][j]) printf("A[%d][%d] = 1\n", i, j);
			//if(h3[i][j]) printf("h3[%d][%d] = 1\n", i, j);
		}
	if(mn.fst == -1 || mn3.fst == -1) {
		if(mn.fst != -1 || mn3.fst != -1) return false;
		puts("YES");
		ni = nj = 0;
		return true;
	}
	//puts("===A");
	//for(int i = 0; i < 12; i++)
	//	for(int j = 0; j < 12; j++)
	//		printf("%c%c", ".*"[A[i + 1006][j + 1006]], " \n"[j == 11]);
	//puts("===h3");
	//for(int i = 0; i < 12; i++)
	//	for(int j = 0; j < 12; j++)
	//		printf("%c%c", ".*"[h3[i + 1006][j + 1006]], " \n"[j == 11]);
	di = mn.i - mn3.i;
	dj = mn.j - mn3.j;
	di = -di;
	dj = -dj;
	ni = di; nj = dj;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if(i + di >= 0 && i + di < N && j + dj >= 0 && j + dj < N && A[i][j] != h3[i + di][j + dj])
				return false;
	puts("YES");
	return true;
	printf("%d %d\n", oj - dj, oi - di);
	exit(0);
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("kids.in", "r", stdin);
	freopen("kids.out", "w", stdout);
#endif
	pii mn1 = read(h1);
	pii mn2 = read(h2);
	pii mn3 = read(h3);
	//printf("(%d, %d) (%d, %d) (%d, %d)\n", mn1.i - d, mn1.j - d, mn2.i - d, mn2.j - d, mn3.i - d, mn3.j - d);
	if(test(mn1.i - mn2.i, mn1.j - mn2.j, h1, h2, h3, mn3)) printf("%d %d\n", -oj, -oi);
	else if(test(mn3.i - mn1.i, mn3.j - mn1.j, h3, h1, h2, mn2)) printf("%d %d\n", oj - nj, oi - ni);
	else if(test(mn3.i - mn2.i, mn3.j - mn2.j, h3, h2, h1, mn1)) printf("%d %d\n", -(oj - nj), -(oi - ni));
	else puts("NO");
}

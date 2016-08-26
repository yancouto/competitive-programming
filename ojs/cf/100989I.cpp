#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = 112345;
int p[5] = {1, 5, 10, 20, 50};
int m[N][5];
int f[N], ch[N], pi[N];
int M[5];

int main() {
	int i, j, k, n, x;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &f[i]);
		int tot = 0;
		for(j = 0; j < 5; j++) {
			scanf("%d", &m[i][j]);
			tot += m[i][j] * p[j];
		}
		ch[i] = tot - f[i];
		pi[i] = i;
	}
	sort(pi, pi + n, [](int i, int j) { return ch[i] < ch[j]; });
	for(k = 0; k < n; k++) {
		i = pi[k];
		for(j = 0; j < 5; j++)
			M[j] += m[i][j];
		for(j = 4; j >= 0; j--)
			while(p[j] <= ch[i] && M[j]) {
				ch[i] -= p[j];
				M[j]--;
			}
		if(ch[i]) { puts("-1"); return 0; }
	}
	for(i = 0; i < n; i++)
		printf("%d ", pi[i] + 1);
	putchar('\n');
}

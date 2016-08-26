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
const int N = 212;

int n, m;
double a[N][N];

int solve() {
	int ct = 0;
	for(int i = 0; i < n; i++) {
		int mx = i;
		for(int j = i + 1; j < n; j++)
			if(abs(a[j][i]) > abs(a[mx][i]))
				mx = j;
		swap_ranges(a[i], a[i] + m, a[mx]);
		if(abs(a[i][i]) < 1e-6) continue;
		ct++;
		for(int j = i + 1; j < n; j++) {
			for(int k = i + 1; k < m; k++)
				a[j][k] -= (a[j][i] / a[i][i]) * a[i][k];
			a[j][i] = 0;
		}
	}
	return ct;

}

int main() {
	int i, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(n < m) scanf("%lf", &a[i][j]);
			else scanf("%lf", &a[j][i]);
	if(n > m) swap(n, m);
	printf("%d\n", solve());
}

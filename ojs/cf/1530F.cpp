#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const int modn = 31607;
inline int mod(int x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
int a_prime[30][30];
int a[30][30];

const int INV = mod(mod(22125 * 22125), mod(22125 * 22125));

int solve() {
	

}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			scanf("%d", &a_prime[i][j]);
			a_prime[i][j] = mod(a_prime[i][j] * INV);
			a[i][j] = a_prime[i][j];
		}
	int pfull_lr = solve();
	int pmaind = 1;
	for(int i = 0; i < n; i++) {
		pmaind = mod(pmaind * a[i][i]);
		a[i][i] = 1;
	}
	int pboth = pmaind;
	int pinvd = 1;
	int pmaind_lr = mod(pmaind * solve());
	for(int i = 0; i < n; i++) {
		pboth = mod(pboth * a[i][n - i - 1]);
		pinvd = mod(pinvd * a[i][n - i - 1]);
		a[i][n - i - 1] = 1;
	}
	int pboth_lr_raw = solve();
	int pboth_lr = mod(pboth * pboth_lr_raw);
	for(int i = 0; i < n; i++) {
		if (i == n - i - 1) {
			a[i][i] = a_prime[i][i];
		} else {
			pinvd = mod(pinvd * a[i][i]);
		}
	}
	int pinvd_lr = mod(pinvd * solve());
	int ans = mod(mod(pfull_lr + (pmaind - pmaind_lr + modn) + (pinvd - pinvd_lr + modn) - pboth_lr + modn) + mod(pboth * mod(1 - pboth_lr_raw + modn)));
	printf("%d\n", ans);
}

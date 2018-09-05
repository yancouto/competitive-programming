#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif
const int N = 112345;
int a[N], eq[N], nx[N], p[N];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	nx[n - 1] = -1;
	int fst = n - 1;
	int lst = n - 1;
	memset(eq, -1, sizeof eq);
	for(i = n - 2; i >= 0; i--) {
		if(a[i] == 1) {
			nx[lst] = i;
			nx[i] = -1;
			lst = i;
		} else if(eq[a[i]] == -1) {
			nx[i] = fst;
			fst = i;
			eq[a[i]] = i;
		} else {
			int j = eq[a[i]];
			nx[i] = nx[j];
			nx[j] = i;
			eq[a[i]] = i;
		}
	}
	for(i = 1; i <= n; i++) {
		p[fst] = i;
		fst = nx[fst];
	}
	for(i = 0; i < n; i++) printf("%d ", p[i]);
	putchar('\n');
}

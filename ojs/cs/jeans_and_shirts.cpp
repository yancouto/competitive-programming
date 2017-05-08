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
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n, m, k;
int a[2123], b[2123];

int main() {
	int i, j;
	scanf("%d %d %d", &n, &m, &k);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(j = 0; j < m; j++)
		scanf("%d", &b[j]);
	int tot = 0;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			tot += (abs(a[i] - b[j]) >= k);
	printf("%d\n", tot);
}

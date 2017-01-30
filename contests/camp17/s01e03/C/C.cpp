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

int n;

int p[1123];

int main() {
	int i, j, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &p[i]);
	for(k = 1; ; k++) {
		for(i = 0; i < n; i++) {
			if(ceil((k * p[i] - k / 2.) / 100.) >= k * (p[i] + .5) / 100.)
				break;
		}
		if(i == n) break;
	}
	printf("%d\n", k);
}

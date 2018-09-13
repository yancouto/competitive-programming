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

const int N = 1123;

char a[N], b[N];

int main() {
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %s %s", &n, a, b);
		int best = 0;
		for(int d = - (n - 1); d <= (n - 1); d++) {
			int cur = 0;
			for(int i = 0; i < n; i++) {
				if(i + d < 0 || i + d >= n || abs(a[i + d] - b[i]) > 1)
					cur = 0;
				else {
					cur++;
					best = max(best, cur);
				}
			}
		}
		if(best * 2 >= n) puts("POSITIVE");
		else puts("NEGATIVE");
	}
}

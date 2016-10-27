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

const int N = 12;

ll best;
ll curr;
ll inp;
ll pw;
int mask;
int n;
char str[N];

ll calc (ll x) {
	return min(pw - abs(x-inp), abs(x-inp));
}

ll brute (int i) {
	if (i == n) {
		if (best == -1 || calc(curr) > calc(best) || (calc(curr) == calc(best) && curr < best))
			best = curr;
	}
		
	for (ll k = 0; k < 10; k++) {
		if (mask&(1<<k)) continue;
		
		curr *= 10;
		curr += k;
		mask |= (1<<k);
		brute(i+1);
		mask -= (1<<k);
		curr /= 10;
	}
}

int main () {
	best = -1;
	
	scanf(" %s", str);
	n = strlen(str);
	inp = atol(str);

	pw = 1;
	for (int i = 0; i < n; i++)
		pw *= 10;

	brute(0);

	if (best < pw/10)
		printf("0");
	printf("%lld\n", best);
}
